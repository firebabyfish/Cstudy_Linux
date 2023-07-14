#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    struct passwd* user;
    if (argc < 2)
    {
        fprintf(stderr, "Error Usage.\n");
        exit(1);
    }
    // user = getpwuid(atoi(argv[1])); //需要用atoi将argv[1]强转为整型
    // //printf("%s\n", user->pw_name);
    // puts(user->pw_name); //为字符直接用puts输出即可
    user = getpwnam(argv[1]);
    printf("%d\n", user->pw_uid);

    exit(0);
}