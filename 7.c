#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// 4 pipe
int main(void)
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    wait(NULL);
    if (pid == 0)
    {
        close(fd[0]);

        printf("Child: Child PID: %d\n", getpid());

        char message[30];

        snprintf(message, sizeof(message),
                 "Hello from child PID: %d", getpid());

        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);
    }
    else
    {

        close(fd[1]);

        printf("Parent: Parent PID: %d\n", getpid());

        char buffer[99];

        ssize_t bytes_read = read(fd[0], buffer, sizeof(buffer));

        if (bytes_read > 0)
        {
            printf("Parent: %s\n", buffer);
        }

        close(fd[0]);

        wait(NULL);
    }

    return 0;
}