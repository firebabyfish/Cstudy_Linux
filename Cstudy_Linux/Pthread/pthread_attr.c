/*
    int pthread attr init(pthread attr t *attr);
        - 初始化线程属性变量

    int pthread attr destroy(pthread attr t *attr);
        - 释放线程属性资源

    int pthread attr getdetachstate(const pthread attr t *attr, int*detachstate);
        - 获取线程分离的状态属性

    int pthread attr setdetachstate(pthread attr t *attr, intdetachstate);
        - 设置线程分离的状态属性

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
    // 设置线程分离状态属性
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // 创建子线程
    pthread_t tid;
    int ret = pthread_create(&tid, &attr, callback, NULL);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error1 : %s\n", errstr);
    }

    // 获取线程分配的栈空间大小
    size_t size;
    pthread_attr_getstacksize(&attr, &size);
    printf("stack size : %ld\n", size);

    // 打印主线程和子线程的ID
    printf("child tid : %ld, main tid : %ld\n", tid, pthread_self());

    pthread_exit(NULL);

    return 0;
}