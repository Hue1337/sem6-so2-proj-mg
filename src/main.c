#include "solution.h"

int main() {
    int philosophers_amount;
    
    printf("Provide the amount of philisophers:\n");
    scanf("%d", &philosophers_amount);
    
    if (philosophers_amount > 0) {
        printf("Starting the dining philosphers problem...\n");
        run(philosophers_amount);
    } else {
        printf("Quiting due the incorrect amount of philosophers...\n");
    }
    
    return 0;
}

