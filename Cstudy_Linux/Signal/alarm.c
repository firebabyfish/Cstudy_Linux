/*
    #include <unistd.h>
    unsigned int alarm(unsigned int seconds);
        - 功能: 设置定时器(闹钟) 。函数调用，开始倒计时，当倒计时为0的时候，
                函数会给当前的进程发送一个信号：SIGALARM
        - 参数:
            - seconds: 倒计时的时长，单位:秒。如果参数为0，定时器无效(不进行倒计时）
                        取消一个定时器，通过alarm(e)
        - 返回值:
            - 之前没有定时器，返回0
            - 之前有定时器，返回之前的定时器剩余的时间
        
    - SIGALARM : 默认终止当前进程，每一个进程都有且只有唯一一个定时器

    alarm函数是不阻塞的

*/

// 一秒钟电脑能数多少个数
#include <stdio.h>
#include <unistd.h>

/*
    实际的时间 = 内核时间 + 用户时间 + 消耗时间
    进行文件IO操作的时候比较浪费时间定时器，与进程的状态无关(自然定时法) 。
    无论进程处于什么状态，alarm都会计时

*/

int main()
{
    alarm(1);
    int i = 0;

    while (1)
    {
        printf("%d\n", i++);
    }
    

    return 0;
}