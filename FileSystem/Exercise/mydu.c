#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <glob.h>

#define PATSIZE 1024

static int path_noloop(const char* path)
{
    char* pos;
    pos = strrchr(path, '/'); //查找字符在指定字符串中从右面开始的第一次出现的位置，如果成功，返回该字符以及其后面的字符
    if (pos == NULL)
        exit(1);
    if (strcmp(pos+1, ".") == 0 || strcmp(pos+1, "..") == 0) //判断是否为/.，是的话则返回0防止死循环
        return 0;
    return 1;
}

static int64_t mydu(const char* path) //__int64_t 为longlong类型
{
    int i;
    static struct stat statres; //创建stat结构体存储文件信息
    static char nextpath[PATSIZE]; //不需要横跨递归的数据可以优化到静态区缓解栈空间的使用
    glob_t globres;
    int64_t sum = 0;

    if (lstat(path, &statres) < 0) //将path文件信息传入statres，失败小于0
    {
        perror("lstat()");
        exit(1);
    }
    if (!S_ISDIR(statres.st_mode)) //判断该文件是否为目录，若不是执行下列操作
        return  statres.st_blocks; //返回空间大小

    strncpy(nextpath, path, PATSIZE); //将path打印到nextpath中
    strncat(nextpath, "/*", PATSIZE); //往nextpath后面追加 /*
    if (glob(nextpath, 0, NULL, &globres) < 0) //分析nextpath包含的目录并判断是否成功
    {
        perror("glob()");
        exit(1);
    }

    strncpy(nextpath, path, PATSIZE); //重新覆盖nextpath，便于下面添加 .隐藏文件
    strncat(nextpath, "/.*", PATSIZE); //往nextpath后面追加 /.*
    if (glob(nextpath, GLOB_APPEND, NULL, &globres) < 0) //此处位图需选用追加，否则会将前面的内容覆盖
    {
        perror("glob()");
        exit(1);
    }

    sum = statres.st_blocks;
    for (i = 0; i <  globres.gl_pathc; i++)
    {
        if (path_noloop(globres.gl_pathv[i]))
            sum += mydu(globres.gl_pathv[i]); //此处使用递归直至mydu参数为非目录
    }

    globfree(&globres);
    return sum;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Error Usage.\n");
        exit(1);
    }

    printf("%lld\n", mydu(argv[1])/2);
    exit(0);
}