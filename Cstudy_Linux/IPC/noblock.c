#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/*
    设置管道非阻塞
    int flags = fcntl(fd[0], F_GETFL);    // 获取原来的flag
    flags |= O_NONBLOCK;            // 修改flag
    fcntl(fd[0], F_SETFL, flags);   // 设置新的flag
*/

int main()
{
    // 在fork之前创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if (ret == -1)
    {
        perror("pipe()");
        exit(0);
    }

    // 创建子进程 
    pid_t pid = fork();
    if (pid > 0)    // 父进程
    {
        printf("I am parent  process. pid : %d\n", getpid());
        // 关闭写端
        close(pipefd[1]);
        // 创建从管道的读取端读数据
        char buf[1024];

        //修改为非阻塞
        int flags = fcntl(pipefd[0], F_GETFL);    // 获取原来的flag
        flags |= O_NONBLOCK;            // 修改flag
        fcntl(pipefd[0], F_SETFL, flags);   // 设置新的flag

        while (1)
        {
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("len : %d\n", len);
            printf("parent receive is : %s, pid : %d\n", buf, getpid());
            memset(buf, 0 , 1024);
            sleep(1);
        }
    }
    else if (pid == 0)    // 子进程
    {
        printf("I am child process. pid : %d\n", getpid());
        // 关闭读端
        close(pipefd[0]);
        // 向管道中写入数据
        while (1)
        {
            char *str = "I am child!";
            write(pipefd[1], str, strlen(str));
            sleep(5);
        }
    }

    return 0;
}