#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#include "PhilosopherState.h"

int PH_AMOUNT;

enum PhilosopherState* state;
pthread_mutex_t mutex;
pthread_mutex_t* forks;
pthread_cond_t* condition;

void* philosopher(void* num);
void take_forks(int index);
void put_forks(int index);
void test(int index);

void run(int pha) {
    PH_AMOUNT = pha;
    pthread_t threads[PH_AMOUNT];
    int philosophers_ids[PH_AMOUNT]; // Philosophers indexes in the tab.

    state = malloc(PH_AMOUNT * sizeof(enum PhilosopherState));
    forks = malloc(PH_AMOUNT * sizeof(pthread_mutex_t));
    condition = malloc(PH_AMOUNT * sizeof(pthread_cond_t));

    // Mutex initialization
    pthread_mutex_init(&mutex, NULL);

    for (int i=0; i<PH_AMOUNT; ++i) {
        pthread_mutex_init(&forks[i], NULL);
        pthread_cond_init(&condition[i], NULL);
        philosophers_ids[i] = i;
    }

    // Creating threads
    for (int i=0; i<PH_AMOUNT; ++i) {
        pthread_create(&threads[i], NULL, philosopher, &philosophers_ids[i]);
    }

    // Threads joining the main thread
    for (int i=0; i<PH_AMOUNT; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Destroying the mutex
    pthread_mutex_destroy(&mutex);
    for (int i=0; i<PH_AMOUNT; ++i) {
        // Destroy mutexes for every fork and condition (?)
        pthread_mutex_destroy(&forks[i]);
        pthread_cond_destroy(&condition[i]);
    }

    free(state);
    free(forks);
    free(condition);
}

void* philosopher(void* num) {
    int index = *(int*)num;
    while (true) {
        printf("Philosopher[%d] is THINKING\n", index + 1); // From 1 to 5 - user friendly.
        sleep(1);
        take_forks(index);
        printf("Philosopher[%d] is EATING\n", index + 1); // ===||===
        sleep(2);
        put_forks(index);
    }
}


void take_forks(int index) {
    // Locking the resource
    pthread_mutex_lock(&mutex);

    state[index] = HUNGRY;
    printf("Philosopher[%d] is HUNGRY\n", index + 1); // ===||===
    test(index);
    while (state[index] != EATING) {
        pthread_cond_wait(&condition[index], &mutex);
    }

    // Unlocking the resource
    pthread_mutex_unlock(&mutex);
}

void put_forks(int index) {
    // Locking again
    pthread_mutex_lock(&mutex);

    state[index] = THINKING;
    printf("Philosopher[%d] put down his fork and now is THINKING\n", index + 1);

    test((index + PH_AMOUNT - 1) % PH_AMOUNT);
    test((index + 1) % PH_AMOUNT);

    // Unlocking again
    pthread_mutex_unlock(&mutex);
}

void test(int index) {
    if (state[index] == HUNGRY && state[(index+PH_AMOUNT-1)%PH_AMOUNT] != EATING && state[(index+1)%PH_AMOUNT] != EATING) {
        state[index] = EATING;
        pthread_cond_signal(&condition[index]);
    }
}