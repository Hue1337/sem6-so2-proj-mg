#include "solution.h"

int main() 
{
    int philosophers_amount;
    printf("Provide the amount of philisophers:\n");
    scanf("%d", &philosophers_amount);
    run(philosophers_amount);
    return 0;
}

