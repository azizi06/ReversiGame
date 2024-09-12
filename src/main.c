#include <stdio.h>

#include "raylib.h"
#include "map.h"
#include "set.h"
#include "moveset.h"
#include "GameLoop.h"
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>


// Function prototypes

int main() {
    char input[2];
    srand(time(NULL));
    printf("1 - to play with ai \n2 - 2 players game \nEnter your choice : ");
    fgets(input,sizeof(input),stdin);
    int player = atoi(input);
    switch (player){
    case  1:
        playWithAI();
        break;
    case  2:
        playTwoPlayerGame();
        break;
    
    default:
        printf("\nwrong input");
        break;
    }
    return 0;
}



