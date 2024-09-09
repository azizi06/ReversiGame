#include "GameLoop.h"
#include "reversi.h"
#include <time.h>

void playWithAI();
void playTwoPlayerGame();
void trainAI();

void playWithAI();
void playTwoPlayerGame(){
    srand(time(NULL));
    int random;
    struct Reversi* game = new_reversi();
    while (game->isgame_over(game))
    {
        game->print(game);
    }
    
}
void trainAI();