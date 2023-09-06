/*
    使用多线程实现卖票
    一共3个窗口，总共100张票

*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

int tickets = 0;

void *selltickets(void *arg)
{
    while (tickets <= 100)
    {
        printf("tid : %ld, 正在售出第%d张票.\n", pthread_self(), ++tickets);
    }
}

int main()
{
    pthread_t tid_1;
    pthread_t tid_2;
    pthread_t tid_3;

    // 创建三个子线程
    int ret_tid1 = pthread_create(&tid_1, NULL, selltickets, NULL);
    if (ret_tid1 != 0)
    {
        char *errstr = strerror(ret_tid1);
        printf("error : %s\n", errstr);
    }
    int ret_tid2 = pthread_create(&tid_2, NULL, selltickets, NULL);
    if (ret_tid2 != 0)
    {
        char *errstr = strerror(ret_tid2);
        printf("error : %s\n", errstr);
    }
    int ret_tid3 = pthread_create(&tid_3, NULL, selltickets, NULL);
    if (ret_tid3 != 0)
    {
        char *errstr = strerror(ret_tid3);
        printf("error : %s\n", errstr);
    }

    // 连接子进程
    ret_tid1 = pthread_join(tid_1, NULL);
    if (ret_tid1 != 0)
    {
        char *errstr = strerror(ret_tid1);
        printf("error : %s\n", errstr);
    }
    ret_tid2 = pthread_join(tid_2, NULL);
    if (ret_tid2 != 0)
    {
        char *errstr = strerror(ret_tid2);
        printf("error : %s\n", errstr);
    }
    ret_tid3 = pthread_join(tid_3, NULL);
    if (ret_tid3 != 0)
    {
        char *errstr = strerror(ret_tid3);
        printf("error : %s\n", errstr);
    }

    // 退出主线程
    pthread_exit(NULL);

    return 0;
}