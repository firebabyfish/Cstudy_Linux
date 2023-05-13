#include <stdio.h>
#include <stdlib.h>

int main()
{
    char buf[1024];
    int  year = 2023, month = 5, day = 9;

    sprintf(buf, "%d-%d-%d", year, month, day); //使用sprintf可以将" "中的内容打印到buf中 等同于itoa（没有itoa这个函数）
    puts(buf);

    char str[] = "123456";
    printf("%d\n", atoi(str)); //把串转化为整型,遇见字母会自动停止

    exit(0);
}