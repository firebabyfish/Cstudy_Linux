#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

//#define PAT "/etc/a*.conf"
//#define PAT "/etc/*" //必须有* 所有文件
#define PAT "/etc/.*" //隐藏文件

#if 0
static int errfunc_(const char* errpath, int eerrno) //glob 的第三个参数，若是有需要可以使用
{
    puts(errpath); //打印出错路径
    fprintf(stderr, "ERROR MSG : %s\n", strerror(eerrno)); //打印错误
    return 0;
}
#endif

//解析目录
int main(int argc, char* argv[])
{
    int i, err;
    glob_t globres;
    err = glob(PAT, 0, NULL, &globres); //参数依次位：文件名，位图(特殊要求)，失败原因及路径，glob_t结构体(存放解析结果的变量)
    if (err) //0为成功
    {
        printf("error code = %d\n", err);
        exit(1);
    }
    for (i = 0; i < globres.gl_pathc; i++) //glob_t.gl_pathc为读取到的文件数
        puts(globres.gl_pathv[i]); //glob_t.gl_pathv为读取到的文件名

    globfree(&globres); //解析的文件目录需要内存，使用完需要释放
    exit(0);
}