#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    fork();

    wait(NULL);

    printf("Hello World! PID = %d\n", getpid());

    return 0;
}