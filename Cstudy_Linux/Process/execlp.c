/*
    #include <unistd.h>
    int execlp(const char* path, const char* arg, ...);
        -会到环境变量中查找指定的可执行文件，找到了就执行，找不到就执行不了
        -参数：
            -file：需要执行的可执行文件的文件名
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
        execlp("ls", "ls", "-l", NULL);
        printf("I am child process\n");
    }

    for (int i = 0; i < 3; i++)
        printf("i = %d  pid : %d\n", i, getpid());

    return 0;
}