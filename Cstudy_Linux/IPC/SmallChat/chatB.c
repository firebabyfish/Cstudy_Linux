#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DATASIZE 128

int main()
{
    int ret = 0;
    // 判断管道文件是否存在
    if (access("fifo1", F_OK) == -1)
    {
        printf("管道不存在，创建管道\n");
        ret = mkfifo("fifo1", 0664);
        if (ret == -1)  // 判断管道是否创建成功
        {
            perror("mkfifo()");
            exit(0);
        }
    }
    if (access("fifo2", F_OK) == -1)
    {
        printf("管道不存在，创建管道\n");
        ret = mkfifo("fifo2", 0664);
        if (ret == -1)  // 判断管道是否创建成功
        {
            perror("mkfifo()");
            exit(0);
        }
    }

    // 以只读方式打开fifo1，在fifo1读数据
    int fdr = open("fifo1", O_RDONLY);
    if (fdr == -1)
    {
        perror("open()");
        exit(0);
    }
    printf("打开管道fifo1成功，等待读取...\n");

    // 以只写方式打开fifo2，在fifo2写数据
    int fdw = open("fifo2", O_WRONLY);
    if (fdw == -1)
    {
        perror("open()");
        exit(0);
    }
    printf("打开管道fifo2成功，等待写入...\n");


    char buf[DATASIZE];
    // 循环读写数据
    while (1)
    {
        // 读数据
        memset(buf, 0, DATASIZE);
        if ((ret = read(fdr, buf, DATASIZE)) <= 0)
        {
            perror("read()");
            break;
        }
        printf("recv chatA : %s", buf);

        // 写数据
        memset(buf, 0, DATASIZE);
        fgets(buf, DATASIZE, stdin);    // 获取标准输入的数据
        if ((ret = write(fdw, buf, strlen(buf))) == -1)
        {
            perror("write()");
            break;;
        }

    }

    close(fdw);
    close(fdr);

    return 0;
}