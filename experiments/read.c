#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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

    while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区

        while( written < n ){
            ssize_t w = write( STDOUT_FILENO , buffer + written , n - written );

            if( w <= 0 ){
                if( w == -1 )
                    perror("write");
                close(fd);
                return 2;
            }                           // write 错误后打印错误信息及退出（暂时不防 EINTR）

            written += w; 
        }                           

        written = 0;                // 整体是防止 write() 发生短写的写法

    }

    if( n == -1 ){                  // 读取错误的处理
        perror("read");
        close(fd);
        return 2;
    }

    close(fd);          // 标准结束的处理
    return 0;
}