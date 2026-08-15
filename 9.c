#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//5.2. receiver reads before sender sends
int main(void)
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0)
    {
        close(fd[0]);

        sleep(3);

        write(fd[1], "Delayed message", 16);

        close(fd[1]);
        exit(0);
    }
    else
    {
        char buffer[100];

        close(fd[1]);

        printf("Parent trying to read...\n");

        read(fd[0], buffer, sizeof(buffer));

        printf("Parent received: %s\n", buffer);

        close(fd[0]);
        wait(NULL);
    }

    return 0;
}