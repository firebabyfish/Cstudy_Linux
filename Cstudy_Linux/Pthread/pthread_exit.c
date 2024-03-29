/*
    #include <pthread.h>
    void pthread_exit(void *retval);
        - 功能:终止一个线程，在哪个线程中调用，就表示终止哪个线程
        - 参数:
            retval:需要传递一个指针，作为一个返回值，可以在pthread_join()中获取到.

    #include <pthread.h>
    pthread_t pthread_self(void);
        - 功能：获取当前线程的线程ID

    int pthread_equal(pthread_t t1, pthread_t t2);
        - 功能: 比较两个线程ID是否相等
            不同的操作系统，pthread_t类型的实现不一样，有的是无符号的长整型，有的是使用结构体去实现的。
        

*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *callback(void *arg)
{
    printf("Child thread...\n");
    printf("Child thread ID : %ld\n", pthread_self());
    return NULL;
}

int main()
{
    // 创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error : %s\n", errstr);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    }

    printf("tid : %ld   Main thread ID : %ld\n", tid, pthread_self());

    // 让主线程退出，当主线程退出时，不会影响其他正常运行的线程
    pthread_exit(NULL);

    return 0;
}