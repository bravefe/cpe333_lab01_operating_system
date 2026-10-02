#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{
    int count = 0;

    while (1)
    {
        pid_t pid = fork();        
        count++;
        printf("Successfully called fork() %d times.\n", count);
        wait(NULL);
    }

    return 0;
}