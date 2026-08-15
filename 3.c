#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// parent die first
int main(void)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Child: PID = %d, initial PPID = %d\n",getpid(), getppid());

        sleep(4);

        printf("Child: New PPID = %d\n", getppid());
        printf("Child not dead yet...\n");
    }
    else
    {
        printf("Parent: PID = %d\n", getpid());
        printf("Parent not dead yet...\n");
        sleep(2);
        printf("The parent was brutally murdered, but the child is still running.\n");
        exit(0);
    }
    system("ps -f");
    return 0;
}