/*
    #include <pthread.h>
    int pthread_mutex_init(pthread_mutex_t *restrict mutex,
        const pthread_mutexattr_t *restrict attr);
        - 初始化互斥量
        - 参数 :
            - mutex : 需要初始化的互斥量变量
            - attr : 互斥量相关的属性，NULL
        - restrict : C语言的修饰符，被修饰的指针，不能由另外的一个指针进行操作
        - e.g : pthread mutex t *restrict mutex = xxx;
                pthread mutex t * mutex1 = mutex;

    int pthread_mutex_destroy(pthread_mutex_t *restrict mutex)
        - 释放互斥量的资源

    int pthread_mutex_lock(pthread_mutex_t *restrict mutex)
        - 加锁，阻塞的，如果有一个线程加锁了，那么其他的线程只能阻塞等待

    int pthread_mutex_trylock(pthread_mutex_t *restrict mutex)
        - 尝试加锁，如果加锁失败，不会阻塞，会直接返回

    int pthread_mutex_unlock(pthread_mutex_t *restrict mutex)
        - 解锁

*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define MAX 10000

int tickets = 0;

// 创建互斥量
pthread_mutex_t mutex;

void *selltickets(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);     // 加锁
        if (tickets < MAX)
        {
            usleep(6000);
            printf("tid : %ld, 正在售出第%d张票.\n", pthread_self(), ++tickets);
        }
        else 
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);   // 解锁
    }
}

int main()
{
    pthread_mutex_init(&mutex, NULL);   // 初始化互斥锁

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

    // 连接子线程
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

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    // 退出主线程
    pthread_exit(NULL);

    return 0;
}