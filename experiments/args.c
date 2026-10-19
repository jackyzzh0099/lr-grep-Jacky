// 本文件为命令行传参小练习

#include <stdio.h>

int main(int argc, char *argv[]){                   //命令行读取
    printf("argc = %d\n",argc);                     //输出 argc
    int i;
    for(i = 0; i < argc; i ++){
        printf("argv[%d] = %s\n", i , argv[i]);     //逐个输出 argc[]
    }
    return 0;
}