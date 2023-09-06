/*
    #include <signal.h>
    int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
        - 功能：检查或者改变信号的处理。信号捕捉
        - 参数：
            - signum : 需要捕捉的信号的编号或者宏值 (信号的名称)
            - act : 捕捉到信号之后的处理动作
            - oldact : 上一次对信号捕捉相关的设置，一般不使用，传递NULL
        - 返回值：成功0，失败-1

        struct sigaction {
            // 函数指针，指向的函数就是信号捕捉到之后的处理函数
            void (*sa handler)(int);

            // 不常用
            void (*sa sigaction)(int, siginfo t *, void *);

            // 临时阻塞信号集，在信号捕捉函数执行过程中，临时阻塞某些信号。
            sigset_t sa_mask;

            //使用哪一个信号处理对捕捉到的信号进行处理
            // 这个值可以是0，表示使用sa handler
            // 也可以是SA_SIGINFO表示使用sa_sigaction
            int sa_flags;

            // 被废弃
            void (*sa_restorer)(void);

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

void myAlarm(int num)
{
    printf("捕捉的信号的编号是：%d\n", num);
    printf("xxxxxxx\n");
}

// 过3s以后，每2s定时一次
int main()
{
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = myAlarm;
    sigemptyset(&act.sa_mask);   // 清空临时阻塞信号集
    // 注册信号捕捉
    sigaction(SIGALRM, &act, NULL);

    struct itimerval new_value;
    // 设置间隔的时间
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;
    // 设置延迟的时间
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL);
    printf("Clock is running...\n");
    if (ret == -1)
    {
        perror("setitimer()");
        exit(0);
    }

    while(1);

    return 0;
}