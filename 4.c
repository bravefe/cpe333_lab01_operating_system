#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// child die first
int main(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child: PID = %d\n", getpid());
        printf("Child not dead YET...\n");

        printf("The child fell from high place, but the parent did nothing and is still running outside.\n");
    }
    else
    {
        
        printf("Parent: PID = %d, initial PPID = %d\n",getpid(), getppid());
        printf("Parent not dead yet... and is waiting for the child to die.\n");
        wait(NULL);
        printf("Parent: New PPID = %d\n", getppid());
        printf("Parent is left alive alone...\n");
    }
    system("ps -f");
    return 0;
}