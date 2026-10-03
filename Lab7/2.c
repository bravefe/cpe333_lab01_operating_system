#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
sem_t forks[N];

int left(int p) {return p;}
int right(int p) {return (p + 1) % N;}

void think(int p) {
    printf("Philosopher %d is thinking\n", p);
    sleep(1);
}

void eat(int p) {
    printf("Philosopher %d is eating\n", p);
    sleep(2);
}

void getforks(int p) {
    if (p == 4) {
        printf("Philosopher %d tries to get RIGHT fork %d\n",p, right(p));
        sem_wait(&forks[right(p)]);
        printf("Philosopher %d got RIGHT fork %d\n", p, right(p));
        sleep(1);
        printf("Philosopher %d tries to get LEFT fork %d\n", p, left(p));
        sem_wait(&forks[left(p)]);
        printf("Philosopher %d got LEFT fork %d\n", p, left(p));
    }
    else {
        printf("Philosopher %d tries to get LEFT fork %d\n",p, left(p));
        sem_wait(&forks[left(p)]);
        printf("Philosopher %d got LEFT fork %d\n", p, left(p));
        sleep(1);
        printf("Philosopher %d tries to get RIGHT fork %d\n", p, right(p));
        sem_wait(&forks[right(p)]);
        printf("Philosopher %d got RIGHT fork %d\n", p, right(p));
    }
}

void putforks(int p) {
    sem_post(&forks[left(p)]);
    sem_post(&forks[right(p)]);
    printf("Philosopher %d put down forks %d and %d\n", p, left(p), right(p));
}

void *philosopher(void *arg) {
    int p = *(int *)arg;
    while (1)
    {
        think(p);
        getforks(p);
        eat(p);
        putforks(p);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int id[N];

    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}