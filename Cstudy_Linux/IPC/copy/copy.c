// 使用内存映射实现文件拷贝的功能
/*
    思路:
        1.对原始的文件进行内存映射
        2.创建一个新文件(拓展该文件)
        3.把新文件的数据映射到内存中
        4.通过内存拷贝将第一个文件的内存数据拷贝到新的文件内存
        5.释放资源
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    // 1.打开需要被复制的文件并创建新文件
    int fdo = open("China.txt", O_RDWR);
    if (fdo == -1)
    {
        perror("open()");
        exit(0);
    }
    int fdn = open("cpy.txt", O_RDWR | O_CREAT, 0664);
    if (fdn == -1)
    {
        perror("open()");
        exit(0);
    }

    // 2.获取原始文件大小
    int size = lseek(fdo, 0, SEEK_END);
    if (size == -1)
    {
        perror("lseek()");
        exit(0);
    }

    // 3.对新创建的文件进行拓展
    truncate("cpy.txt", size);
    write(fdn, " ", 1);

    // 4.分别做内存映射
    void *ptro = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fdo, 0);
    if (ptro == MAP_FAILED)
    {
        perror("mmap()");
        exit(0);
    }
    void *ptrn = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fdn, 0);
    if (ptrn == MAP_FAILED)
    {
        perror("mmap()");
        exit(0);
    }

    // 5.内存拷贝
    memcpy(ptrn, ptro, size);

    // 6.释放资源
    munmap(ptrn, size);
    munmap(ptro, size);
    close(fdn);
    close(fdo);

    return 0;
}