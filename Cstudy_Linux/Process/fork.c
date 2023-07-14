#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    printf("[%d]: Begin!\n", getpid());
    fflush(NULL);   //用于刷新缓冲区
    pid = fork();
    if(pid < 0)     //error
    {
        perror("fork");
        exit(1);
    }
    if(pid == 0)    //Child
    {
        printf("[%d]: Child is working!\n", getpid());
    }
    else            //Parent
    {
        printf("[%d]: Parent is working!\n", getpid());
    }

    printf("[%d]: End!\n",getpid());
    //getchar();    使界面得以停留以用于ps命令观察进程
    exit(0);
}