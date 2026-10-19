#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int suit( char *line , char *pattern , ssize_t line_len , ssize_t pattern_len , int ignore_case ){        // 该函数用以扫描 line 里面有没有 pattern
    if( pattern_len > line_len )
        return 0;                               // 若 pattern_len 比 line_len 还大，那么不可能匹配

    if( pattern_len == 0 )
        return 1;                               // 若 pattern_len = 0，即空字符串，则按照题目要求匹配所有行

    int l , t ;                                 // 外层、内层循环标识量
    for( l = 0 ; l <= line_len - pattern_len ; l ++ ){       // 从 line 的首元素开始，区长度为 pattern_len 的一小段与 pattern 对比
        for( t = 0 ; t < pattern_len ; t ++ ){
            if( pattern[t] != line[ l + t ] ){               // 若不完全符合，则将 line 上用以对比的这一小段向后移动 1 个字节
                if( line[ l + t ] >= 65 && line[ l + t ] <= 90  && line[ l + t ] >= 97 && line[ l + t ] <= 122
                    && ignore_case == 1 
                    && ( line[ l + t ] + 32 == pattern[t] || pattern[t] + 32 == line[ l + t ] ) ){
                    continue;                   // 加入 -i 判断，可以忽略大小写不匹配
                }
                else
                    break;
            }
        }
        if( t == pattern_len )                         // 直到连续 pattern_len 个元素扫描完成，即 line 中存在完全符合 patten 的段
            return 1;
    }
    
    return 0;
}


int main(int argc, char *argv[]){
    int i, j, k = 0;                        // 用于循环控制的变量

    int show_line_number = 0;
    int ignore_case = 0;
    int count_only = 0;                 // 3 个 “选项” 参数

    int option = 0;                     // 为了便于参数解析，新建一个状态表示 “是否检验到 ‘状态’ 参数”
    int pat = 0;                        // 为了便于参数解析，新建一个状态表示 “是否检验到 pattern ”

    char *pattern = NULL;               // pattern 存放的位置
    char *file[ argc ];                 // 文件名列表

    int file_num = 1;                   // 文件计数器

    ssize_t pattern_len = 0;            // pattern 长度计数器，初始化为 0 

    int suit_or_no = 0;                 // 设置表示该 line 是否存在匹配 pattern 的段的状态参数。
    int suit_num = 0;                   // 表示某文件里匹配的 line 的数量
    
    int line_num = 0;                   // 行号计数器

    for( i = 1; i < argc; i++ ){

        if( argv[i][0] == '-' && argv[i][1] != 0){
            j = 1;
            option = 1;

            while( argv[i][j] != 0 ){
            if( argv[i][j] == 'n' )
                show_line_number = 1;
            if( argv[i][j] == 'i' )
                ignore_case = 1;
            if( argv[i][j] == 'c' )
                count_only = 1;
            if( argv[i][j] != 'n' && argv[i][j] != 'i' && argv[i][j] != 'c' ){
                fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
                return 2;
            }
                
            j ++;

            }                                                   // 识别到 “选项” 时，设置 3 个 “选项” 参数

        }

        if( (pat == 0 && argv[i][0] != '-') || ( pat == 0 && option == 0 ) ){
            pattern = argv[i] ;

            while( pattern[pattern_len] != 0 ){
                pattern_len += 1;
            }                                       // pattern 长度计算

            pat = 1;
            break;                                   // 读取 pattern 并防止重复读取以及 pattern 再次被识别成文件名
        }

    }

    if( pat == 0 ){
        fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
        return 2; 
    }
                                              // 未解析到 pattern 时返回 2

    for( i = i + 1 ; i < argc ; i ++ ){
        file[file_num] = argv[i];
        file_num ++ ;
    }                                                   // 逐个解析文件名

    // printf("show_line_number = %d\n", show_line_number);
    // printf("ignore_case = %d\n", ignore_case);
    // printf("count_only = %d\n", count_only);
    // printf("pattern: %s\n", pattern);
    // printf("How many files: %d\n", file_num - 1);                // 打印状态
    
    if( file_num != 1){
        for( i = 1; i < file_num; i ++ ){
            if( file_num > 2 ){                         // 只有大于一个文件时才打印文件名
                printf("%s: \n", file[i] );
            }
            
            int fd = open(file[i], O_RDONLY);       // 以只读打开 argv[1] 中文件名对应的文件，并生成文件描述符

            if( fd == -1 ){
                perror("lrg: open file fail");
                return 2;
            }

            char buffer[16];                // 创建缓存区（当前设置 16 字节）
            ssize_t n, written = 0;                      // 设置变量 n, written 用以存储 read() 和 write() 的返回值

            char *line = NULL;
            size_t line_len = 0;
            size_t line_cap = 64;

            line = malloc( line_cap ) ;
            if( line == NULL ){
                perror("lrg: malloc fail");
                return 2;
            }

            while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区

                for( size_t i = 0 ; i < n ; i ++ ){
                    if( buffer[i] == '\n' ){
                        line_num += 1;                  // 行号计数器 +1
                        suit_or_no = suit( line , pattern , line_len , pattern_len , ignore_case );
                        if( suit_or_no == 1 ){
                            suit_num += 1;                      // 匹配数量计数器 +1
                        }
                        if( suit_or_no == 1 && count_only == 0 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配且未选择 -c 时才输出
                            if( show_line_number == 1 ){
                                printf("%d: ", line_num );
                                fflush(stdout);                         // 强制把 printf() 尚未输出的缓冲内容刷新出去
                            } 
                            write( STDOUT_FILENO , line , line_len );
                            write( STDOUT_FILENO , "\n" , 1 );
                        }
                        suit_or_no = 0;
                        line_len = 0;                           // 遇到换行符时标准输出当前 line 里的行
                    }
                    else{

                        if( line_len == line_cap ){
                            char *tmp = realloc( line , line_cap * 2);
                            if( tmp == NULL ){
                                perror("lrg: realloc fail");
                                free( line );
                                close(fd);
                                return 2;
                            }
                            else{
                                line = tmp;
                                line_cap *= 2;
                            }                               // 若行内存不够，将扩容到原来 2 倍
                        }
                        
                        line[line_len] = buffer[i];
                        line_len += 1;                      // 将普通字符添加至 line 末尾
                    }
                }

            }

            if( n == -1 ){                  // 读取错误的处理
                perror("lrg: read file fail");
                free( line );
                close(fd);
                return 2;
            }

            if( n == 0 && line_len > 0){                // 若读取结束，但 line_len != 0，说明 line 里面还有最后一行的内容 → 用以处理文件末尾没有 \n 的情况。
                line_num += 1;                          // 行号计数器 +1
                suit_or_no = suit( line , pattern , line_len , pattern_len , ignore_case );
                if( suit_or_no == 1 ){
                    suit_num += 1;                      // 匹配数量计数器 +1
                }
                if( suit_or_no == 1 && count_only == 0 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配且未选择 -c 时才输出
                    if( show_line_number == 1 ){
                        printf("%d: ", line_num );
                        fflush(stdout);                 // 强制把 printf() 尚未输出的缓冲内容刷新出去
                    }
                    write( STDOUT_FILENO , line , line_len );
                    write( STDOUT_FILENO , "\n" , 1 );
                }

                line_len = 0;                                
            }
            suit_or_no = 0;

            if( count_only == 1 ){
                printf("%d\n", suit_num );
            }
            suit_num = 0;           // 匹配计数器归零
            line_num = 0;
            free( line );
            close(fd);          // 标准结束的处理
            
        }
    }                                                   // 逐个打印文件名

    return 0;
}