/*
    #include <pthread.h>
    int pthread cancel(pthread t thread);
        - 功能: 取消线程 (让线程终止)
            取消某个线程，可以终止某个线程的运行
            但是并不是立马终止，而是当子线程执行到一个取消点，线程才会终止
            取消点:系统规定好的一些系统调用，我们可以粗略的理解为从用户区至内核区的切换，这个位置称位取消点

*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *callback(void *arg)
{
    printf("child tid : %ld\n", pthread_self());
    for (int i = 0; i < 5; i++)
    {
        printf("child : %d\n", i);
    }
    return NULL;
}

int main()
{
    // 创建子线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error1 : %s\n", errstr);
    }

    // 取消线程
    ret = pthread_cancel(tid);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error1 : %s\n", errstr);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    }

    // 打印主线程和子线程的ID
    printf("child tid : %ld, main tid : %ld\n", tid, pthread_self());

    pthread_exit(NULL);

    return 0;
} 