/*
    #include <unistd.h>
    int execlp(const char* path, const char* arg, ...);
        -参数：
            -path：需要指定的执行的文件的路径或者名称
            -arg：是执行可执行文件所需要的参数列表
                第一个参数无作用，一般写的是执行程序的名称
                第二个参数往后，就是程序执行所需要的参数列表
                参数需以NULL结尾（哨兵）

        -返回值：
            只有当调用失败，才会有返回值，返回-1，并且设置errno
            如果调用成功，没有返回值

*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        printf("I am parent process  pid : %d\n", getpid());
        sleep(1);
    }
    else if (pid == 0)
    {
        execl("hello", "hello", NULL);
        printf("I am child process\n");
    }

    for (int i = 0; i < 3; i++)
        printf("i = %d  pid : %d\n", i, getpid());

    return 0;
}