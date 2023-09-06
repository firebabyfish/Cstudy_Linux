/*
    include <pthread.h>
    int pthread detach(pthread t thread);
        - 功能：分离一个线程。被分离的程在终止的时候，会自动释放资源返回给系统
            1.不能多次分离，会产生不可预料的行为
            2.不能去连接一个已经分离的线程，会报错
        - 参数：需要分离的线程的ID
        - 返回值：成功0，失败返回错误号

*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *callback(void *arg)
{
    printf("child tid : %ld\n", pthread_self());
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

    // 打印主线程和子线程的ID
    printf("child tid : %ld, main tid : %ld\n", tid, pthread_self());

    // 设置子线程分离
    ret = pthread_detach(tid);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error2 : %s\n", errstr);
    }

    // 设置分离后，再连接看是否由错误
    ret = pthread_join(tid, NULL);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error3 : %s\n", errstr);
    }

    pthread_exit(NULL);

    return 0;
}