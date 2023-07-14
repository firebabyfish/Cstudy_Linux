#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, int* argv[])
{
    FILE* fp = NULL;
    char* linebuf = NULL; //
    size_t linesize = 0;
    if (argc < 2)
    {
        fprintf(stderr, "Usage:%s <src_file>\n", argv[0]);
        exit(1);
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    while(1)
    {
        if (getline(&linebuf, &linesize, fp) < 0) //读取fp每一行
            break;
        printf("%d\n", strlen(linebuf)); //打印每行的字符数
	    printf("%d\n", linesize); //打印当前文件已开辟的空间大小，根据需要会自动扩大
    }

    fclose(fp);
    exit(0);
}
