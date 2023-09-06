
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

void myFunc(int num)
{
    printf("捕获的信号编号：%d\n", num);
    // while (1)
    //     wait(NULL);

    while (1)
    {
        int ret = waitpid(-1, NULL, WNOHANG);   // 设置非阻塞
        if (ret > 0)
        {
            printf("Child die   pid : %d\n", ret);
        }
        else if (ret == 0) // 还有子进程活着
        {
            break;
        }
        else if (ret == -1) // 子进程回收完毕
        {
            break;
        }
    }
}

int main()
{
    // 提前设置好阻塞信号集，阻塞SIGCHLD，因为有可能在注册信号前子进程就运行结束了
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    pid_t pid;
    for (int i = 0; i < 20; i++)
    {
        pid = fork();
        if (pid == 0)
            break;
    }
    if (pid > 0)
    {
        // 父进程
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myFunc;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL);
        
        sigprocmask(SIG_UNBLOCK, &set, NULL); // 解除非阻塞

        while (1)
        {
            printf("Parent process  pid : %d\n", getpid());
            sleep(2);
        }
    }
    else if (pid == 0)
    {
        // 子进程
        printf("Child Process   pid : %d\n", getpid());
    }


    return 0;
}