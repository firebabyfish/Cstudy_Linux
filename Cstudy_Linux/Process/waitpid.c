/*
    #include <sys/types.h>
    #include <sys/wait.h>
    pid_t waitpid(pidd_t pid, int *wstatus, int options);
        功能：回收指定进程号的子进程，可以设置是否阻塞
        参数：
            - pid
                pid > 0 : 某个进程的pid
                pid = 0 : 回收当前进程组的所有子进程
                pid = -1 : 回收所有的子进程，相当于wait()
                pid < -1 : 回收某个进程组的组id的绝对值，回收指定进程组中的子进程
            - int *wstatus
                进程退出时的状态信息，传入的是一个int类型的地址，传出参数
            -options
                0 : 阻塞
                WNOHANG : 非阻塞
        返回值：
            - > 0 : 返回子进程的id
            - = 0 : options = WNOHANG，表示还有子进程活着
            - = -1 : 错误或者没有子进程
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