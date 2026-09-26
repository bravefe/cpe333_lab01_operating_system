#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Shared variables for Peterson's Algorithm
int flag[2] = {0, 0};
int turn;

// Shared resource
int counter = 0;

// Peterson's entry section
void enter_critical_section(int process) {
    int other = 1 - process;

    flag[process] = 1;
    turn = other;

    while (flag[other] && turn == other) {
        // Busy waiting
    }
}

// Peterson's exit section
void exit_critical_section(int process) {
    flag[process] = 0;
}

// Thread function
void *process(void *arg) {
    int process_id = *(int *)arg;

    for (int i = 0; i < 100000; i++) {

        // Entry section
        enter_critical_section(process_id);

        // Critical section
        counter++;

        // Exit section
        exit_critical_section(process_id);
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    int id1 = 0;
    int id2 = 1;

    // Create two threads
    pthread_create(&thread1, NULL, process, &id1);
    pthread_create(&thread2, NULL, process, &id2);

    // Wait for both threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final counter value: %d\n", counter);

    return 0;
}