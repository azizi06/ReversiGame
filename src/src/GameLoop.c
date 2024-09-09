#include "GameLoop.h"
#include "reversi.h"
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void playWithAI();
void playTwoPlayerGame();
void trainAI();

void playWithAI();
void playTwoPlayerGame(){
    srand(time(NULL));
    int random = rand() %2;
 


    struct Reversi* game = new_reversi();
    while (game->isgame_over(game))
    {   

        char input_x[1] = NULL;
        char input_y[1] = NULL;
        game->print(game);
        int Player = game->player;
        if(Player == B){
            printf("\nBlack Player Turn ");
        }else{
            printf("\nBlack Player Turn ");
        }
        while(input_x == NULL || input_y == NULL){
            printf("Enter ROW :");
            fgets(input_x,sizeof(input_x),stdin);

            printf("ENTER COLUMN :");
            fgets(input_x,sizeof(input_x),stdin);

        }
        if(strncmp(input_x,"q",1)==0){
            printf("Quiting Game");
                break;
        }

       
        
    }
    
}
void trainAI();