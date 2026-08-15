#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// don't put this in final pdf
int fork_count(int count)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        // fork failed
        return count;
    }
    else if (pid == 0)
    {
        printf("Successfully called fork() %d times.\n", count + 1);
        int result = fork_count(count + 1);
        printf("Maximum successful fork() calls: %d\n", result);
        exit(0);
    }
    else
    {
        wait(NULL);
        return count;
    }
}

int main(void)
{
    fork_count(0);
    return 0;
}