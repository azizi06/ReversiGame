#include <stdio.h>
#include "GameLoop.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "minmax.h"
int main()
{
    int n = 20;
    int player = W;
    float number_of_success = 0;

    for (int i = 0; i < n; i++)
    {
        int winner =   MinMaxAgentWihtRandomPlayer( player);
        if (winner == player)
        {
            number_of_success+=1.0f;
        }
    }
    float success_rate = number_of_success / (float)n;
    printf("\nnumber_of_success is %f",number_of_success);
    printf("\nsuccess rate is %f\n", success_rate);
    return 0;
}
