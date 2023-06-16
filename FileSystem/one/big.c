#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int fd;
    if (argc < 2)
    {
        fprintf(stderr, "Usage...");
        exit(1);
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600); //创建一个新文件
    if (fd < 0)
    {
        perror("open()");
        exit(1);
    }

    lseek(fd, 5LL*1024LL*1024LL*1024LL-1LL, SEEK_SET); //将文件扩充为一个5G的文件 //用LL才能保证不会整数溢出

    write(fd, "", 1); //将文件写为空洞文件

    close(fd);
    exit(0);
}