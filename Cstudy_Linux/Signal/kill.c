/*
    #include <sys/types.h>
    #include <signal.h>

    int kill(pid t pid, int sig);
        - 功能:给任何的进程或者进程组pid，发送任何的信号 sig
        - 参数:
            - pid : 
                > : 将信号发送给指定的进程
                = : 将信号发送给当前的进程组
                = -1 : 将信号发送给每一个有权限接收这个信号的进程
                < -1 : pid = 某个进程组ID取反
            - sig : 需要发送的信号的编号或者是宏值

    int raise(int sig);
        - 功能：给当前进程发送信号
        - 参数：
            - sig : 要发送的信号
        - 返回值：
            - 成功0，失败非0

    void abort(void);
        - 功能：发送SIGABRT信号给当前进程，杀死当前进程
        
*/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        // 父进程
        printf("Parent process.\n");
        sleep(2);
        printf("Kill child process.\n");
        kill(pid, SIGINT);
    }
    else if (pid == 0)
    {
        // 子进程
        int i = 0;
        for (i = 0; i < 5; i++)
        {
            printf("Child process.\n");
            sleep(1);
        }
    }

    return 0;
}