#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define PAT "/etc"

int main()
{
    DIR* dp; //定义一个目录流指针
    struct dirent* cur; //创建一个接受读取文件目录的结构体
    dp = opendir(PAT); //打开目录流
    if (dp == NULL) //若为空打开失败
    {
        perror("opendir()");
        exit(1);
    }
    while ((cur = readdir(dp)) != NULL) //读取目录流dp的数据
        puts(cur->d_name); //打印读取数据中的文件名

    closedir(dp); //关闭开辟的目录流内存
    exit(0);
}