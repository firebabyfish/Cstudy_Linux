#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
    FILE* fp = NULL;
    int count = 0;

    //检测是否有对象
    if (argc < 2)
    {
        fprintf(stderr, "Usage:%s <src_file>\n", argv[0]);
        exit(1);
    }

    //打开所要计数的文件
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    //开始计数
    while (fgetc(fp) != EOF)
    {
        count++;
    }

    printf("count = %d\n", count);
    fclose(fp);
    exit(0);

}