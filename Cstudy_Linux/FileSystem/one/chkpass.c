#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <shadow.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char* input_passwd;
    char* crypt_passwd;
    struct spwd* shadow_line;
    if (argc < 2)
    {
        fprintf(stderr, "Error Usage.\n");
        exit(1);
    }

    input_passwd = getpass("PassWord:"); //获取密码，括号内容为需要显示的内容
    if (input_passwd == NULL)
    {
        perror("getpass()");
        exit(1);
    }
    shadow_line = getspnam(argv[1]); //获取argv[1]在shadow文件中对应的加密密码串
    if (getspnam == NULL)
    {
        perror("getspnam()");
        exit(1);
    }
    crypt_passwd = crypt(input_passwd, shadow_line->sp_pwdp); //这里不截断而直接使用sp_pwdp是因为密码串只能显示到3$前相当于截断 
    if (crypt_passwd == NULL)
    {
        perror("crypt()");
        exit(1);
    }

    //输入密码与保存的密码串做对比
    if (strcmp(shadow_line->sp_pwdp, crypt_passwd) == 0)
        puts("ok!");
    else
        puts("fail!");

    exit(0);
}