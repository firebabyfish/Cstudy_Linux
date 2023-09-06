/*
    读写锁的类型 pthread rwlock t
    int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, 
        const pthread_rwlockattr_t *restrict attr);
    int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
    int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

    案例：8个线程操作同一个全局变量
    3个线程不定时写这个全局变量，5个线程不定时的读这个全局变量

*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int num = 0;
pthread_rwlock_t rwlock;

void *writeNum(void *arg)
{
    while (1)
    {
        pthread_rwlock_wrlock(&rwlock);
        printf("wrtieNum... tid : %ld, num = %d\n", pthread_self(), ++num);
        pthread_rwlock_unlock(&rwlock);
        usleep(1000);
    }
}

void *readNum(void *arg)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("readNum... tid : %ld, num = %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(1000);
    }
}

int main()
{
    pthread_rwlock_init(&rwlock);
    pthread_t wrtids[3], rdtids[5];
    for (int i = 0; i < 3; i++)
    {
        if (i < 3)
        {
            pthread_create(&wrtids[i], NULL, writeNum, NULL);
            pthread_create(&rdtids[i], NULL, readNum, NULL);
        }
        pthread_create(&rdtids[i], NULL, readNum, NULL);
    }

    for (int i = 0; i < 3; i++)
    {
        if (i < 3)
        {
            pthread_detach(wrtids[i]);
            pthread_detach(rdtids[i]);
        }
        pthread_detach(rdtids[i]);
    }

    pthread_rwlock_destroy(&rwlock);
    pthread_exit(NULL);
    return 0;
}