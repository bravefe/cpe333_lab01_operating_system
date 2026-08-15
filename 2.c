#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();
    wait(NULL);

    if (pid == 0)
    {
        // Child process
        printf("Child: PID = %d\n", getpid());
    }
    else
    {
        // Parent process waits for the child
        printf("Parent: PID = %d\n", getpid());
    }

    return 0;
}