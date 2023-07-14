#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

/*
-y  year
-m  month
-d  day
-H  hour
-M  minute
-S  second
*/

#define TIMEMAXSIZE     1024

int main(int argc, char* argv[])
{
    FILE* fp = stdout;
    time_t now_time;
    struct tm* tm;
    char strtime[TIMEMAXSIZE];
    int ret;
    char fstrtime[TIMEMAXSIZE];

    fstrtime[0] = '\0';

    now_time = time(NULL); //读取时间戳
    tm = localtime(&now_time); //将 时间戳转化为结构体

    while(1)
    {
        ret = getopt(argc, argv, "-y:mdH:ms"); //加-可以在后面添加argv参数，加:可以在后面增加判断条件
        if (ret < 0)
            break;
        // if (fstrtime[0] != '\0')
        // {
        //     strncat(fstrtime, "-", TIMEMAXSIZE);
        // }
        switch (ret)
        {
        case 1:
            if (fp == stdout) //先入为主的判断
            {
                fp = fopen(argv[optind-1], "w");
                if (fp == NULL)
                {
                    perror("fopen()");
                    fp = stdout;          
                }  
            }      
            break;
        case 'y':
            if (strcmp(optarg, "2") == 0) //加了-之后后面可以追加判断条件分别执行不同的效果
                strncat(fstrtime, "%y", TIMEMAXSIZE);
            else if (strcmp(optarg, "4") == 0)
                strncat(fstrtime, "%Y", TIMEMAXSIZE);
            else
                fprintf(stderr, "Invalied argument!\n");
            break;
        case 'm':
            strncat(fstrtime, "%m", TIMEMAXSIZE);
            break;
        case 'd':
            strncat(fstrtime, "%d", TIMEMAXSIZE);
            break;
        case 'H':
            if (strcmp(optarg, "12") == 0)
                strncat(fstrtime, "%I", TIMEMAXSIZE);
            else if (strcmp(optarg, "24") == 0)
                strncat(fstrtime, "%H", TIMEMAXSIZE);
            else
                fprintf(stderr, "Invalied argument!\n");
            break;
        case 'M':
            strncat(fstrtime, "%M", TIMEMAXSIZE);
            break;
        case 'S':
            strncat(fstrtime, "%S", TIMEMAXSIZE);
            break;
        }
    }

    strncat(fstrtime, "\n", TIMEMAXSIZE); //fputs没有自带换行，需要手动添加换行符
    strftime(strtime, TIMEMAXSIZE, fstrtime, tm); //将结构体中的属性转化为字符串（查手册）
    fputs(strtime, fp);
    //puts(strtime);

    if (fp != stdout)
        fclose(fp);
    exit(0);
}