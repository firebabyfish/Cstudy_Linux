#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static off_t flen(const char* fname) //注意数据类型需要用宏定义类型
{
    struct stat statres; //创建stat结构体
    if (stat(fname, &statres) < 0) //判断stat是否运行成功
    {
        perror("stat()");
        exit(1);
    }
    return statres.st_size; //返回文件大小
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    printf("%lld\n", (long long)flen(argv[1])); //可通过makefile改变，此处使用long long强转
    exit(0);
}