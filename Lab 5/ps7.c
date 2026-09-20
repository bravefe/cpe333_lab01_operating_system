#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>

/*
    ./ps7 x y

    x = number of threads (machines)
    y = mode (0 = without forced context switch, 1 = forced context switch)

    task 1: ./ps7 1 0
    task 2: ./ps7 4 0
    task 3: ./ps7 4 1
*/

long money;

int mode;

#define JACKPOT_PAYOUT 1000
#define MAX_JACKPOT_PER_MACHINE 500000


void *SlotMachineJackpotPayout(void *arg)
{
    int jackpotOnThisMachine = *(int *)arg;

    for (int i = 0; i < jackpotOnThisMachine; i++) {

        if (mode == 0) {
            money = money - JACKPOT_PAYOUT;
        } 
        else {
            long temp = money;
            temp = temp - JACKPOT_PAYOUT;
            sched_yield();
            money = temp;
        }
    }

    return NULL;
}


int main(int argc, char *argv[])
{
    int machine = (argc > 1) ? atoi(argv[1]) : 1;
    mode = (argc > 2) ? atoi(argv[2]) : 0;

    srand(time(NULL));
    int *jackpotPerMachine = malloc(sizeof(int) * machine);


    for (int i = 0; i < machine; i++) {

        jackpotPerMachine[i] = (rand() % MAX_JACKPOT_PER_MACHINE) + 1;
    }

    long startingMoney = 0;
    for (int i = 0; i < machine; i++) {
        startingMoney +=(long)jackpotPerMachine[i] *JACKPOT_PAYOUT;
    }
    money = startingMoney;


    pthread_t *tid = malloc(sizeof(pthread_t) * machine);
    int *machineNumber = malloc(sizeof(int) * machine);


    for (int i = 0; i < machine; i++) {
        pthread_create(&tid[i], NULL, SlotMachineJackpotPayout, &jackpotPerMachine[i]);
    }


    for (int i = 0; i < machine; i++) {
        pthread_join(tid[i], NULL);
    }


    long expected = 0;


    printf("== Settings ==\n");
    printf("machine             = %d\n", machine);
    printf("JACKPOT PAYOUT      = %d\n",JACKPOT_PAYOUT);
    printf("MAX JACKPOT/MACHINE = %d\n",MAX_JACKPOT_PER_MACHINE);
    printf("mode                = %s\n\n",
           mode ? "forced" : "not forced");


    printf("== Jackpots per Machine ==\n");

    for (int i = 0; i < machine; i++) {
        printf("machine %d = %d jackpots\n", i, jackpotPerMachine[i]);
    }


    printf("\n== Slot Machine ==\n");
    printf("starting money    : $%ld\n", startingMoney);
    printf("expected remaining: $%ld\n", expected);
    printf("actual remaining  : $%ld\n\n", money);


    if (money != expected) {
        printf("> RACE CONDITION DETECTED (%ld)\n", money - expected);

    } else {
        printf("> payout correctly\n");
    }


    free(tid);
    free(machineNumber);
    free(jackpotPerMachine);

    return 0;
}