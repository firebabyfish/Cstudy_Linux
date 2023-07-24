/*
    #include <sys/mman.h>
    void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
        - 功能：将一个文件或者设备的数据映射到内存中
        - 参数：
            - void *addr : NULL，由内核指定
            - length : 要映射的数据长度，这个值不能为0，建议使用文件的长度
                获取文件的长度：stat，lseek
            - prot : 对申请的内存映射区的操作权限
                - PROT_EXEC : 可执行的权限
                - PROT_READ : 读权限
                - PROT_WRITE : 写权限
                - PROT_NONE : 没有权限
                要操作映射内存，必须要有读的权限。
                PROT_READ、PROT READ|PROT WRITE
            - flags :
                MAP_SHARED : 映射区的数据会自动和磁盘文件进行同步，进程间通信必须要设置这个选项
                MAP PRIVATE :不同步，内存映射区的数据改变了，对原来的文件不会修改，会重新创建一个新的文件（copy on write）
            - fd : 需要映射的那个文件的文件描述符
                - 通过open得到，open的是一个磁盘文件
                - 注意:文件的大小不能为0，open指定的权限不能和prot参数有冲突
                    prot : PROT READ                 open:只读/读写
                    prot : PROT_READ | PROT_WRITE    open:读写
                    offset: 偏移量，一般不用，必须指定的是4k的整数倍，0表示不偏移
        - 返回值：
            成功：返回创建的内存的首地址
            失败：返回MAP_FAILED（即(void *) -1）

    int munmap(void *addr, size_t length);
        - 功能：释放内存映射
        - 参数：
            - addr : 要释放的内存的首地址
            - length : 要释放的内存大小，要和mmap函数中的length值一样
    使用内存映射实现进程间通信:
        1.有关系的进程(父子进程)
            - 还没有子进程的时候
            - 通过唯一的父进程，先创建内存映射区
            - 有了内存映射区以后，创建子进程
            - 父子进程共享创建的内存映射区
        2.没有关系的进程间通信
            - 准备一个大小不是0的磁盘文件
            - 进程1 通过磁盘文件创建内存映射区
                - 得到一个操作这块内存的指针
            - 进程2 通过磁盘文件创建内存映射区
                - 得到一个操作这块内存的指针
            - 使用内存映射区通信
        
        注意:内存映射区通信，是非阻塞
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int main()
{
    // 1.打开一个文件
    int fd = open("test.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open()");
        exit(0);
    }
    int size = lseek(fd, 0, SEEK_END);    // 获取文件长度

    // 2.创建内存映射区
    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap()");
        exit(0);
    }

    // 3.创建子进程
    pid_t pid = fork();
    if (pid > 0)
    {
        // 父进程
        wait(NULL);
        char buf[64];
        strcpy(buf, (char *)ptr);
        printf("Read data : %s\n", buf);
    }
    else if (pid == 0)
    {
        // 子进程
        strcpy((char *)ptr, "Hello, I am child.\n");
    }
    else 
    {
        perror("fork()");
        exit(0);
    }

    // 4.关闭内存映射区
    munmap(ptr, size);
    close(fd);

    return 0;
}
