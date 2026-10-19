#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if ( argc != 2){
        fprintf(stderr, "usage: read FILE\n");
        return 2;
    }                   // // 检查命令行参数数量是否正确，若否，则向 stderr 中写入错误提示信息并打印


    int fd = open(argv[1], O_RDONLY);       // 以只读打开 argv[1] 中文件名对应的文件，并生成文件描述符

    if( fd == -1 ){
        perror("open");
        return 2;
    }

    char buffer[16];                // 创建缓存区（当前设置 16 字节）
    ssize_t n, written = 0;                      // 设置变量 n, written 用以存储 read() 和 write() 的返回值

    char *line = NULL;
    size_t line_len = 0;
    size_t line_cap = 64;

    line = malloc( line_cap ) ;
    if( line == NULL ){
        perror("malloc fail");
        return 2;
    }

    while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区

        for( size_t i = 0 ; i < n ; i ++ ){
            if( buffer[i] == '\n' ){
                write( STDOUT_FILENO , line , line_len );
                write( STDOUT_FILENO , "\n" , 1 );
                line_len = 0;                           // 遇到换行符时标准输出当前 line 里的行
            }
            else{

                if( line_len == line_cap ){
                    char *tmp = realloc( line , line_cap * 2);
                    if( tmp == NULL ){
                        perror("realloc fail");
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
        perror("read");
        free( line );
        close(fd);
        return 2;
    }

    if( n == 0 && line_len > 0){
        write( STDOUT_FILENO , line , line_len );
        write( STDOUT_FILENO , "\n" , 1 );
        line_len = 0;                                // 若读取结束，但 line_len != 0，说明 line 里面还有最后一行的内容 → 用以处理文件末尾没有 \n 的情况。
    }

    free( line );
    close(fd);          // 标准结束的处理
    return 0;
}