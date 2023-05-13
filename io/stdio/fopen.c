#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    int count = 0;
    FILE* fp = NULL;

    while(1)
    {
        fp = fopen("temp", "r");
        if (fp == NULL)
        {
            //打印错误的三种方法：
            // fprintf(stderr, "errno = %d\n", errno); //此处需要包含头文件<errno.h>
            // fprintf(stderr, "fopen : %s\n", strerror(errno));
            perror("fopen()");
            break;
        }
        count++;
    }
    
    printf("count = %d\n" ,count);
    // puts("OK!");
    // fclose(fp); //有打开必须有关闭，互逆操作返回必为堆区数据

    exit(0);
}