#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "Philosopher.h"

void run(int amount) 
{
    // Initialization 
    struct Philosopher philosophers[amount];
    for(int i=0; i<amount; ++i) {
        struct Philosopher p;
        if(i%2 == 1) {
            p.eating = false;
        } else {
            p.eating = false;
        }
        philosophers[i] = p;
        printf("I=%d, eating=%d\n", i, p.eating);
    }
    philosophers[4].eating=true;
    printf("phi[4]: %d\n", philosophers[4].eating);
}

bool can_eat(int index, int amount, struct Philosopher philosophers[]) 
{
    return index-1 < 0 ? !(philosophers[(index-1+amount)%amount].eating && philosophers[(index+1+amount)%amount].eating) : !(philosophers[(index-1)%amount].eating && philosophers[(index+1)%amount].eating);
}