/*
    匿名映射：不需要文件实体进行内存映射
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <sys/stat.h>

int main()
{
    int len = 4096;
    // 1.创建匿名内存映射区
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap()");
        exit(0);
    }

    // 2.父子进程间通信
    pid_t pid = fork();
    if (pid > 0)
    {
        strcpy((char*)ptr, "Hello world!");
        wait(NULL);
    }
    else if (pid == 0)
    {
        sleep(1);
        printf("%s\n", (char*)ptr);
    }
    else if (pid == -1)
    {
        perror("fork()");
        exit(0);
    }

    // 3.释放资源
    int ret = munmap(ptr, len);
    if (ret == -1)
    {
        perror("munmap()");
        exit(0);
    }

    return 0;
}