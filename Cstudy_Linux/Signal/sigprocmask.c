/*
    int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
        - 功能：将自定义信号集中的数据设置到内核中(设置阻塞，解除阻塞，替换)
        - 参数:
            - how : 如何对内核阻塞信号集进行处理
                SIG BLOCK： 将用户设置的阻塞信号集添加到内核中，内核中原来的数据不变（mask | set）
                SIG_UNBLOCK：根据用户设置的数据，对内核中的数据进行解除阻塞（mask &= ~set）
                SIG_SETMASK：覆盖内核中原来的值
            - set : 用户初始化好的自定义信号集
            - oldset : 保存设置之前内核中的阻塞信号集的状态，一般用不上为NULL
        - 返回值：成功0，失败-1

    int sigpending(sigset_t *set);
        - 功能：获取内存中的未决信号集
        - 参数：set，传出参数，保存的是内核中的未决信号集中的信息

*/

// 把所有的常规信号（1-31）的未决信号状态打印到屏幕
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    // 添加2、3到信号集中
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    // 修改内核中的阻塞信号集
    int ret = sigprocmask(SIG_BLOCK, &set, NULL);
    if (ret == -1)
    {
        perror("sigprocmask()");
        exit(0);
    }

    while(1)
    {
        sigset_t pend;
        sigemptyset(&pend);
        sigpending(&pend);

        // 遍历前32位
        for (int i = 1; i < 32; i++)
        {
            if (sigismember(&pend, i) == 1)
                printf("1");
            else if (sigismember(&pend, i) == 0)
                printf("0");
            else
                perror("sigismember");
        }
        printf("\n");
        sleep(2);
    }
}