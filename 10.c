#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0)
    {
        close(fd[0]);

        write(fd[1], "Hello from child 1", strlen("Hello from child") + 1);
        write(fd[1], "Hello from child 2", strlen("Hello from child") + 1);
        write(fd[1], "Hello from child 3", strlen("Hello from child") + 1);

        close(fd[1]);
        exit(0);
    }
    else
    {
        char buffer[99];

        close(fd[1]);

        sleep(2);

        int n = read(fd[0], buffer, sizeof(buffer) - 1);
        buffer[n] = '\0';

        printf("Parent received:\n%s", buffer);

        close(fd[0]);
        wait(NULL);
    }

    return 0;
}