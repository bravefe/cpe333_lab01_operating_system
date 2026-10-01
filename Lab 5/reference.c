/*
 * CPE 333 Operating Systems - Problem Session 7
 * Concurrency and Race Conditions
 *
 * Scenario: a concert venue sells tickets through several sales
 * terminals (threads). All terminals share one "tickets_remaining"
 * counter. Each terminal sells a batch of tickets by decrementing the
 * shared counter once per sale. If the decrement is not atomic, two
 * terminals can read the same value before either writes it back, so a
 * sale gets "lost" and the final count is wrong.
 *
 * Usage:
 *   ./ps7 <num_threads> <sales_per_thread> <mode>
 *     num_threads      : number of sales terminals (threads)
 *     sales_per_thread : tickets each terminal sells
 *     mode             : 0 = plain decrement (counter = counter - 1)
 *                         1 = forced context switch
 *                             (load into register, modify, yield, store)
 *
 *   Task 1: ./ps7 1 500000 0   single thread  -> always correct
 *   Task 2: ./ps7 4 500000 0   multiple threads, natural race
 *   Task 3: ./ps7 4 2000    1  multiple threads, forced race
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

long tickets_remaining;   /* shared variable: the race condition target */
int  sales_per_thread;
int  mode;

void *sales_terminal(void *arg) {
    for (int i = 0; i < sales_per_thread; i++) {
        if (mode == 0) {
            /* Looks like one atomic step, but the compiler turns it into
               load tickets_remaining -> subtract 1 -> store back.
               Two threads' loads/stores can interleave. */
            tickets_remaining = tickets_remaining - 1;
        } else {
            long reg = tickets_remaining;   /* load memory into register */
            reg = reg - 1;                  /* decrease register         */
            sched_yield();                  /* force an untimely switch  */
            tickets_remaining = reg;        /* save register to memory   */
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int num_threads = (argc > 1) ? atoi(argv[1]) : 1;
    sales_per_thread = (argc > 2) ? atoi(argv[2]) : 500000;
    mode = (argc > 3) ? atoi(argv[3]) : 0;

    long starting_tickets = (long)num_threads * sales_per_thread;
    tickets_remaining = starting_tickets;

    pthread_t *tid = malloc(sizeof(pthread_t) * num_threads);
    if (!tid) { perror("malloc"); return 1; }

    for (int i = 0; i < num_threads; i++)
        pthread_create(&tid[i], NULL, sales_terminal, NULL);
    for (int i = 0; i < num_threads; i++)
        pthread_join(tid[i], NULL);

    long expected = 0;  /* every ticket that started should get sold */
    printf("threads=%d sales_per_thread=%d mode=%s\n",
           num_threads, sales_per_thread, mode ? "forced-switch" : "plain");
    printf("starting tickets  : %ld\n", starting_tickets);
    printf("expected remaining: %ld\n", expected);
    printf("actual remaining  : %ld\n", tickets_remaining);
    if (tickets_remaining != expected)
        printf("--> RACE CONDITION DETECTED (%ld sale(s) lost)\n",
               tickets_remaining - expected);
    else
        printf("--> counter correct this run\n");

    free(tid);
    return 0;
}