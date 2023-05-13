#include <stdio.h>
#include <stdlib.h>

/*
- 缓冲区的作用：合并系统调用
- 行缓冲：换行/满了/强制刷新(标准输出即是如此，因为是是终端设备)
- 全缓冲：满了/强制刷新(默认，只要不是终端设备)
- 无缓冲：如stderr，需要立即输出的内容
- setvbuf 
*/

int main()
{
    int i;
    printf("Before while()\n"); //标准输出以换行来刷新缓冲区
    fflush(stdout); //也可以写为fflush(NULL)
    while(1);
    printf("After while()\n");
    fflush(NULL);

    exit(0);
}