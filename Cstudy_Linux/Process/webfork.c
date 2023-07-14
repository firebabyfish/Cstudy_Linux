/*
    #include <sys/types.h>
    #include <unistd.h>

    pid_t fork(void);
        函数的作用：创建子进程
        返回值：
            fork()的返回值会返回两次。一次是在父进程中，一次是在子进程中。
            在父进程中返回创建的子进程的ID，
            在子进程中返回0。
            区分父子进程：通过fork的返回值。
            在父进程中返回-1，表示创建子进程失败，并设置errno。

        父子进程之间的关系：
        区别：
            1.fork()函数的返回值不同
                父进程中：>0，返回子进程的ID
                子进程中：=0
            2.pcb中的一些数据
                当前进程的ID  pid
                当前进程得到父进程的ID  ppid
                信号集

        共同点：
            某些状态下，子进程刚被创建出来，还没有进行任何写数据的操作
                -用户区数据
                -文件描述符表
            
            父子进程对变量是否共享
                -刚开始共享，修改数据之后不共享
                -读时共享，写时拷贝

*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork(); // 创建子进程
    if (pid > 0) //父进程
    {
        printf("ppid: %d\n", getppid());
        printf("I am parent process.  pid: %d  ppid: %d\n", getpid(), getppid());
    }
    else if (pid == 0) //子进程
    {
        printf("I am child process.  pid: %d  ppid: %d\n", getpid(), getppid());
    }

    for (int i = 0; i < 3; i++)
    {
        printf("i = %d,  pid: %d\n", i, getpid());
        sleep(1);
    }

    return 0;
}