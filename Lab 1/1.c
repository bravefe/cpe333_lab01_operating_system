#include <stdio.h>
#include <unistd.h>

int main(void)
{
    fork();

    printf("Hello World! PID = %d\n", getpid());

    return 0;
}