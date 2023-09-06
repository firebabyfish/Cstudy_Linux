/*
    一般情况下，main函数所在的线程我们称之为主线程（主线程），其余创建的线程称为子线程

    #include <pthread.c>
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
        void *(*start_routine) (void *), void *arg);
        - 功能：创建一个子线程
        - 参数:
            - thread : 传出参数，线程创建成功后，子线程的线程ID被写到该变量中
            - attr : 设置线程的属性，一般使用默认值，NULL
            - start_routine : 函数指针，这个函数是子线程需要处理的逻辑代码
            - arg : 给第三个参数的函数传参
        - 返回值：
            成功0，失败errno（该errno与之前使用的不一样，不能用直接用perror）
            获取错误号的信息：char *strerror(int errnum);

*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *callback(void *arg)
{
    printf("Child thread...\n");
    printf("arg : %d\n", *(int*)arg);
    return NULL;
}

int main()
{
    pthread_t tid;
    int num = 10;
    int ret = pthread_create(&tid, NULL, callback, (void*)&num);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    }

    sleep(1);

    return 0;
}