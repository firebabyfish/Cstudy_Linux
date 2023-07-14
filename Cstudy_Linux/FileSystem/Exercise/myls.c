#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>

int main(int argc, char* argv[])
{
    char* workspace;
    size_t size;
    glob_t globres;
    int err;
    if (argc < 1)
    {
        fprintf(stderr, "Error Usege!");
        exit(1);
    }
    if (argc == 1)
    {
        if (getcwd(workspace, size) != NULL)
        {
            if ((err = glob()))
        }
    }
}