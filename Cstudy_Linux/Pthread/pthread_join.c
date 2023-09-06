/*
    #include <pthread.h>
    void pthread_exit(pthread_t thread, void *retval);
        - 功能:
            - 和一个已经终止的线程进行连接
            - 回收子线程的资源
            - 这个函数是阻塞函数，调用一次只能回收一个子线程
            - 一般在主线程中使用
        - 参数:
            - thread : 需要回收的子线程的ID
            - retval : 接收子线程退出时的返回值
        - 返回值:
            成功0，失败错误号
        
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *callback(void *arg)
{
    printf("Child thread...\n");
    printf("Child thread ID : %ld\n", pthread_self());
    sleep(3);
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

    // 主线程调用 pthread_join 回收子线程
    ret = pthread_join(tid, NULL);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error : %s\n", errstr);
    }

    printf("Child thread die!\n");

    // 让主线程退出，当主线程退出时，不会影响其他正常运行的线程
    pthread_exit(NULL);

    return 0;
}