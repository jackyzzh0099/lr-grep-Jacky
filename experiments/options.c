#include <stdio.h>

int main(int argc, char *argv[]){
    int i, j;                        // 用于循环控制的变量

    int show_line_number = 0;
    int ignore_case = 0;
    int count_only = 0;                 // 3 个 “选项” 参数

    int option = 0;                     // 为了便于参数解析，新建一个状态表示 “是否检验到 ‘状态’ 参数”
    int pat = 0;                        // 为了便于参数解析，新建一个状态表示 “是否检验到 pattern ”

    char *pattern = NULL;               // pattern 存放的位置
    char *file[ argc ];                 // 文件名列表

    int file_num = 1;                   // 文件计数器


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

    printf("show_line_number = %d\n", show_line_number);
    printf("ignore_case = %d\n", ignore_case);
    printf("count_only = %d\n", count_only);
    printf("pattern: %s\n", pattern);
    printf("How many files: %d\n", file_num - 1);                // 打印状态
    
    if( file_num != 1){
        for( i = 1; i < file_num; i ++ ){
            printf("file %d : %s\n", i , file[i]);
        }
    }                                                   // 逐个打印文件名

    return 0;
}