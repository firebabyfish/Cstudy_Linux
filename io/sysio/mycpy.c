/***********************************************************************
习题 : 将mycpy.c程序进行更改，将BUFSIZE的值从128开始放大，并观察进程消耗的时间，
注意性能最佳拐点出现时的BUFSIZE值，以及何时程序会出现问题
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    FILE* sfd = NULL;
    FILE* dfd = NULL;
    int BUFSIZE = 128;
    char buf[BUFSIZE];
    int len, ret, pos, count;
    if (argc < 3)
    {
        fprintf(stderr, "Usage:%s <src_file> <dest_file>\n" ,argv[0]);
        exit(1);
    }

    sfd = open(argv[1], O_RDONLY); //(argv[2], 只读)
    if (sfd < 0)
    {
        perror("open()");
        exit(1);
    }
    dfd = open(argv[2], O_WRONLY|O_CREAT, O_TRUNC, 0600); //(argv[2], 只写 | 无则创建, 有则清空(截断), 权限(用到了O_CREAT))
    if (dfd < 0)
    {
        close(sfd);
        perror("open()");
        exit(1);
    }
    count = 0;
    while (1)
    {
        len = read(sfd, buf, BUFSIZE);
        if (len == BUFSIZE) //如果读入字符数达到BUFSIZE上限，则扩大BUFSIZE
        {
            BUFSIZE *= 2;
            count++;
        }
        if (len < 0) //读文件错误
        {
            perror("read()");
            break;
        }
        if (len == 0) //文件读完
            break;
        pos = 0;
        while (len > 0) //判断是否写完
        {
            write(dfd, buf + pos, len); //以上两种条件不成立则开始写入文件，pos为已写入的字符数
            if (ret < 0) //文件写入错误
            {
                perror("write()");
                exit(1);
            }
            pos += ret;
            len -= ret; //如果写入字符数ret不为len，说明写入中途退出，则减少已写入字符再继续写入
        }
        
    }


    close(dfd);
    close(sfd);
    exit(0);
}