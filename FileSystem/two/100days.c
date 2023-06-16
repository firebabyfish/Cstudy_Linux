#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TIMEMAXSIZE     1024

int main(int argc, char* argv[])
{
    time_t now_time;
    struct tm* tm;
    char* strtime;

    now_time = time(NULL); //读取时间戳
    tm = localtime(&now_time); //将 时间戳转化为结构体
    strftime(strtime, TIMEMAXSIZE, "Now: %Y-%m-%d", tm); //将结构体中的属性转化为字符串（查手册）
    puts(strtime);

    tm->tm_mday += 100;
    mktime(tm); //此处利用mktime的第二功能，将加的天数转化为正确的显示时间
    strftime(strtime, TIMEMAXSIZE, "Later: %Y-%m-%d", tm);
    puts(strtime);

    exit(0);
}