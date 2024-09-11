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
    bool is_over;
    char input_x[10];
    char input_y[10];
    struct Move move;
    struct Reversi* game = new_reversi();
    bool runing = true;
    while (game->isgame_over(game) && runing)
    {          
        //print game to the screen :
        game->print(game);
        int Player = game->player;
        //reading input :
        if(Player == B){
            printf("\nBlack Player Turn ");
        }else{
            printf("\nWhite Player Turn ");
        }
        printf("\nEnter ROW :");
        fgets(input_x,sizeof(input_x),stdin); 
        if(strncmp(input_x,"q",1)==0){
            printf("Quiting Game");
                break;
        }
        printf("ENTER COLUMN :");
        fgets(input_y,sizeof(input_y),stdin);
        if(strncmp(input_y,"q",1)==0){
            printf("Quiting Game");
                break;
        }    
        while (!is_correct_input(game,atoi(input_x),atoi(input_y),game->player)){                  
            printf("\nEnter ROW :");
            fgets(input_x,sizeof(input_x),stdin); 
            if(strncmp(input_x,"q",1)==0){
                printf("Quiting Game");
                    break;
            }
            printf("ENTER COLUMN :");
            fgets(input_y,sizeof(input_y),stdin);
            if(strncmp(input_y,"q",1)==0){
                printf("Quiting Game");
                break;
            }
            }
        //PERFORMING A MOVE :
        move.x = atoi(input_x);
        move.y = atoi(input_y);
        game->move(game,&move);
        //counting score
        game->count(game);
        //Switching Player
        game->next(game);
    }

    game->print(game);
    char winner[15]; 
    (game->winner == W)? strcpy(winner, "white"):strcpy(winner, "Black");
    printf(ANSI_COLOR_BLUE"%s player win"ANSI_RESET,winner);
}
void trainAI(){

}