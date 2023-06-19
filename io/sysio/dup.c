#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "/home/lhy/Cstudy_Linux/io/sysio/tmp/out"

int main()
{
    // close(1); //关闭标准输出
    int fd, dupid;
    fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
    {
        perror("open()");
        exit(1);
    }
    //该操作非原子操作
    // close(1);w
    // dup(fd);
    dupid = dup2(fd, 1); //上述操作的原子操作为:dup2
    if (dupid != 1)
        close(fd);
/************************************************/
    puts("hello!");

    exit(0);
}