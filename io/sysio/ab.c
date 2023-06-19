#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    putchar('a');
    write(1, "b", 1);
    putchar('a');
    write(1, "b", 1);
    putchar('a');
    write(1, "b", 1);
    //bbbaaa    因为write为系统调用直接，而putchar为标准调用先进入了缓冲区

    exit(0);
}