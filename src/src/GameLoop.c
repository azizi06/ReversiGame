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
struct Solver* trainAI(int n);

void playWithAI(){
    struct Reversi* game = new_reversi();
    struct Solver* ai = trainAI(1000);
    char input_x[10];
    char input_y[10];
    bool Quit = false;
    struct Move move;
    ai->player = W;
    while(!game->isgame_over(game)){
        game->print(game);
        
        if(game->player == W){
        printf(ANSI_COLOR_RED"\nWhite Player Turn "ANSI_RESET);       
        struct Move* move = NULL;
        int attemps = 5;
        while(move == NULL && attemps > 0){    
            move = ai->move(ai,game->game_matrix);
            printf("\n[%d]ai choosing move...",attemps);
            attemps--;

        } 
        game->move(game,move);
        printf("\nai choose move (%d,%d)",move->x,move->y);
        free(move);
        }else{
            printf(ANSI_COLOR_GREEN"\nBlack Player Turn "ANSI_RESET);
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
        check_winner(game);
        game->next(game);
    }
    if(!Quit){
        check_winner(game);
        game->print(game);
        char winner[15]; 
        (game->winner == W)? strcpy(winner, "white"):strcpy(winner, "Black");
        printf(ANSI_COLOR_BLUE"\n%s player win"ANSI_RESET,winner);
    }else{
        printf("Quitting Game\n");
    }
    free(game);
    free(ai);
}
void playTwoPlayerGame(){
    srand(time(NULL));
    int random = rand() %2;
    char input_x[10];
    char input_y[10];
    struct Move move;
    struct Reversi* game = new_reversi();
    bool Quit = false;
    while (!game->isgame_over(game))
    {          
        //print game to the screen :
        game->print(game);
        int Player = game->player;
        //reading input :
        if(Player == B){
            printf(ANSI_COLOR_GREEN"\nBlack Player Turn "ANSI_RESET);
        }else{
            printf(ANSI_COLOR_RED"\nWhite Player Turn "ANSI_RESET);       
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
        check_winner(game);
        game->print(game);
        char winner[15]; 
        (game->winner == W)? strcpy(winner, "white"):strcpy(winner, "Black");
        printf(ANSI_COLOR_BLUE"\n%s player win"ANSI_RESET,winner);
    }
   
    
}
void twoBotsgame(){
    struct Reversi* game = new_reversi();
    struct Solver* ai_w = new_solver(0.5,0.5,W);
    struct Solver* ai_b = new_solver(0.5,0.5,B);
    bool Quit = false;

    while(!game->isgame_over(game)){
        game->print(game);
        
        if(game->player == W){
            printf(ANSI_COLOR_RED"\nWhite Player Turn "ANSI_RESET);       
            struct Move* move = NULL;
            int attemps = 5;
            while(move == NULL && attemps > 0){    
                move = ai_w->move(ai_w,game->game_matrix);
                printf("\n[%d]ai_w choosing move...",attemps);
                attemps--;
            } 
            game->move(game,move);
            printf("\nai choose move (%d,%d)",move->x,move->y);
            free(move);
        }else{
            printf(ANSI_COLOR_RED"\nWhite Player Turn "ANSI_RESET);       
            struct Move* move = NULL;
            int attemps = 5;
            while(move == NULL && attemps > 0){    
                move = ai_b->move(ai_b,game->game_matrix);
                printf("\n[%d]ai_b choosing move...",attemps);
                attemps--;
            } 
            game->move(game,move);
            printf("\nai choose move (%d,%d)",move->x,move->y);
            free(move);
        }
        game->count(game);
        //Switching Player
        game->next(game);
    }
    if(!Quit){
        check_winner(game);
        game->print(game);
        char winner[15]; 
        (game->score_w > game->score_b)? strcpy(winner, "white"):strcpy(winner, "Black");
        printf(ANSI_COLOR_BLUE"\n%s player win"ANSI_RESET,winner);
    }else{
        printf("Quitting Game\n");
    }
    ai_w->free(ai_w);ai_b->free(ai_b);
    free(game);
    
}



struct Solver* trainAI(int n){
    struct Solver* ai= new_solver(0.5,1,B);
    bool Quit = false;
    for(int i = 0;i<= n;i++){
        printf("\nTraining ai game %d  ",i);
        struct Reversi* game = new_reversi();
        bool runing = true;
        while(runing){
            //game->print(game);
            ai->player = game->player;
            int old_state[ROWS][COLUMNS];
            copy_2d_array(old_state,game->game_matrix);

            struct Move* move =  ai->move(ai,game->game_matrix);

            if(move == NULL){
                break;
            }
 
                
                game->move(game,move); 
      
                int new_state[ROWS][COLUMNS];
                copy_2d_array(new_state,game->game_matrix);
                game->count(game);
                game->next(game);

                if(game->isgame_over(game)){

                    check_winner(game);
                    if(ai->player == game->winner){
                    ai->update(ai,old_state,move,new_state,1);              
                    }else{
                    ai->update(ai,old_state,move,new_state,-1);                      
                    }
                    runing = false;
                    break;
                }else{       

                    ai->update(ai,old_state,move,new_state,0); 

                }
          
         free(move);
        }
        printf("   The winner is %d",game->winner);
        free(game);   
    }

   return ai;

}