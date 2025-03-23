#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "PhilosopherState.h"

#ifdef _WIN32

#include <windows.h>
#define sleep Sleep

#else

#include <unistd.h>
#endif


pthread_mutex_t mutex;

void* philospher(void* add);

void run(int ph_amount) {
    // Data init
    enum PhilosopherState philosophers[ph_amount];    
    pthread_t pthreads[ph_amount];

    // Creating a thread
    for (int i=0; i<ph_amount; ++i) {
        pthread_create(&pthreads[i], NULL, philosopher, (void*)philosophers);
    }


    // Joining
    for (int i=0; i<ph_amount; ++i) {
        pthread_join(&pthreads[i], NULL);
    }

}

void* philosopher(void* add) {
    while (true) {
        
    }
}