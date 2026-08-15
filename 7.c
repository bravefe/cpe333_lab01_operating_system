#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// 4 pipe
int main(void)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        // Child = sender
        close(fd[0]);

        printf("Child: Child PID: %d\n", getpid());

        char message[100];

        snprintf(message, sizeof(message),
                 "Hello from child PID: %d", getpid());

        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);
    }
    else
    {
        // Parent = receiver
        close(fd[1]);

        printf("Parent: Parent PID: %d\n", getpid());

        char buffer[100];

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