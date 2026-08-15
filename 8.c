#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// 5.1. sender tries to read back its own message
int main(void)
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0)
    {
        char buffer[100];

        write(fd[1], "Hello from child", 17);

        read(fd[0], buffer, sizeof(buffer));

        printf("Child read: %s\n", buffer);

        close(fd[0]);
        close(fd[1]);
        exit(0);
    }
    else
    {
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}