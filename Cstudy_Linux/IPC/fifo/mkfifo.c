/*
    创建FIFO文件
    1.通过命令：mkfifo + 名字
    2.通过函数：int mkfifo(const char *pathname, mode_t mode);

    #include <sys/types.h>
    #include <sys/stat.h>
    int mkfifo(const char *pathname, mode_t mode);
        参数：
            - pathname：管道名称的路径
            - mode：文件的权限（与open的mode用法相同），是一个八进制数
        返回值：
            成功 0，失败 -1

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    if ((access("fifo", F_OK)) == -1)
    {
        printf("管道不存在，创建管道\n");
        int ret = mkfifo("fifo", 0664);
        if (ret == -1)
        {
            perror("mkfifo()");
            exit(0);
        }
    }

    return 0;
}