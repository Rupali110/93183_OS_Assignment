#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int i;
    pid = fork();

    if (pid == 0)
    {
        char *str = "Infotech";
        for (i = 0; str[i] != '\0'; i++)
        {
            putchar(str[i]);
            fflush(stdout);
            sleep(1);
        }
        putchar('\n');
    }
    else
    {
        char *str = "Sunbeam";
        for (i = 0; str[i] != '\0'; i++)
        {
            putchar(str[i]);
            fflush(stdout);
            sleep(1);
        }
        putchar('\n');
        wait(NULL);
    }

    return 0;
}

