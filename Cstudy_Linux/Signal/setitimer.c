/*
    #include <sys/time.h>
    int setitimer(int which, const struct itimerval *new_value,
                    struct itimerval *old_value);

        - 功能：设置定时器(闹钟)，可以替代alarm函数，精度可以达到us，可以实现周期性定时
        - 参数：
            - which : 定时器以什么时间计时
                ITIMER_REAL : 真实时间，时间到达发送SIGALRM（常用）
                ITIMER_VIRTUAL: 用户时间，时间到达，发送SIGVTALRM（少用）
                ITIMER PROF: 以该进程在用户态和内核态下所消耗的时间来计算，时间到达发送SIGPROF

            - new_value: 设置定时器的属性
            struct itimerval {    //定时器的结构体
                struct timeval it_interval; // 每个阶段的时间，间隔时间
                struct timeval it value;    // 延迟多长时间执行定时器
            };
            struct timeval {    // 时间的结构体
                time_t      tv_sec;    // 秒数
                suseconds_t tv_usec;   // 微秒
            };

            - old_value: 记录上一个定时器的时间参数（一般不使用，直接写NULL）

        - 返回值：成功0，失败-1

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// 过3s以后，每2s定时一次
int main()
{
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

    getchar();

    return 0;
}
