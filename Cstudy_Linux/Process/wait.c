/*
    #include <sys/types.h>
    #include <sys/wait.h>
    pid_t wait(int *wstatus);
        功能：等待任意一个子进程结束，如果任意一个子进程结束了，此函数会回收子进程
        参数：int *wstatus
            进程退出时的状态信息，传入的是一个int类型的地址，传出参数
        返回值：
            - 成功：返回回收子进程的id号
            - 失败：-1（所有子进程都结束，调用函数失败）
    调用wait函数的进程会被挂起（阻塞），直到它的一个子进程退出或收到一个不能被忽略的信号，
    如果没有子进程了，函数会立即返回-1，子进程都结束了也会立即返回-1

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    for (int i = 0; i < 5; i++)
    {
        pid = fork();
        if (pid == 0)
            break;
    }

    if (pid > 0)
    {
        while (1)
        {
            printf("parent, pid = %d\n", getpid());
            int ret = wait(NULL);

            if (ret < 0)
            {
                printf("all chidren die!\n");
                break;
            }
            else 
                printf("child[%d] die\n", ret);

            sleep(1);
        }
    }
    else if (pid == 0)
    {
        while (1)
        {
            printf("child, pid = %d\n", getpid());
            sleep(2);
        }
    }

    return 0;
}