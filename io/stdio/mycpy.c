#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* fps = NULL;
    FILE* fpd = NULL;
    int ch;

    if (argc < 3)
    {
        fprintf(stderr, "Usage:%s <src_file> <dest_file>\n" ,argv[0]);
        exit(1);
    }

    fps = fopen(argv[1], "r"); //打开所读文件
    if (fps == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    fpd = fopen(argv[2], "w"); //打开所写文件
    if (fpd == NULL)
    {
        fclose(fps);
        perror("fopen()");
        exit(1);
    }

    while(1)
    {
        ch = fgetc(fps); //获取字符
        if (ch == EOF)
            break;
        fputc(ch, fpd); //写入字符
    }

    fclose(fpd); //关闭所写文件(优先关闭有依赖文件)
    fclose(fps); //关闭所读文件

    exit(0);
}