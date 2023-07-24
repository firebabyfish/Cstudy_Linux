/*
    - 实现 ls | wc -l
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int main()
{
    // 创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if (ret == -1)
    {
        perror("pipe()");
        exit(0);
    }

    // 创建子进程
    pid_t pid = fork();
    if (pid > 0)    //父进程
    {
        //关闭写端
        close(pipefd[1]);
        char buf[1024] = {0};
        int len = -1;
        // 读取读端数据
        while ((len = read(pipefd[0], buf, sizeof(buf)-1)) > 0)
        {
            printf("%s", buf);
            memset(buf, 0, 1024);   //buf每读满一次清空一次，直至将数据完全读取完毕
        }
        wait(NULL);
    }
    else if (pid == 0)  // 子进程
    {
        //关闭读端
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO); // 文件描述符重定向 stdout > pipefd[1]
        execlp("ps", "ps", "aux", NULL);   // 执行ls
        perror("execlp()");
        exit(0);
    }
    else
    {
        perror("fork()");
        exit(0);
    }

    return 0;
}