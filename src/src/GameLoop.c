#include "GameLoop.h"
#include "reversi.h"
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"solver.h"
#include "tools.h"

void playWithAI();
void playTwoPlayerGame();
void trainAI();

void playWithAI(){
    struct Reversi* game = new_reversi();
    struct Solver* ai = new_solver(0.5,0.5,W);
    char input_x[10];
    char input_y[10];
    bool Quit = false;
    struct Move move;
    while(game->isgame_over(game)){
        game->print(game);
        
        if(game->player == W){
        printf("\nwhite Player Turn ");
        struct Move* move = ai->move(ai,game->game_matrix);
        game->move(game,move);
        free(move);
        }else{
            printf("\nBlack Player Turn ");
            char c;getc(stdin);
            if (handel_player_input(game, input_x, input_y) == -1) {
            Quit = true;
            break;  // Quit the game
            }
             //PERFORMING A MOVE :
            move.x = atoi(input_x);
            move.y = atoi(input_y);
            game->move(game,&move);
        }
        game->count(game);
        //Switching Player
        game->next(game);
    }
    if(!Quit){
        game->print(game);
        char winner[15]; 
        (game->winner == W)? strcpy(winner, "white"):strcpy(winner, "Black");
        printf(ANSI_COLOR_BLUE"%s player win"ANSI_RESET,winner);
    }else{
        printf("Quitting Game\n");
    }
}
void playTwoPlayerGame(){
    srand(time(NULL));
    int random = rand() %2;
    char input_x[10];
    char input_y[10];
    struct Move move;
    struct Reversi* game = new_reversi();
    bool Quit = false;
    while (game->isgame_over(game))
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
        if (handel_player_input(game, input_x, input_y) == -1) {
            Quit = true;
            break;  // Quit the game
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
    if(!Quit){
        game->print(game);
        char winner[15]; 
        (game->winner == W)? strcpy(winner, "white"):strcpy(winner, "Black");
        printf(ANSI_COLOR_BLUE"%s player win"ANSI_RESET,winner);
    }else{
        printf("Quitting Game");
    }
   
    
}
void trainAI(){

}