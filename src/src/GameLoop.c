#include "GameLoop.h"
#include "reversi.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "minmax.h"
#include <time.h>

int MinMaxAgentWihtRandomPlayer(int player)
{
    struct Reversi *game = new_reversi();
    bool Quit = false;
    int i = 0; // move count;

    while (!game->isgame_over(game))
    {
        struct Move move = {-1, -1};
        //  game->print(game);
        if (game->player == player)
        { // ai player
            printf("\nai choosing a move...\n");
            int tmp_game_matrix[ROWS][COLUMNS] = {E};
            copy_2d_array(tmp_game_matrix, game->game_matrix);

            struct Move *Agentmove = minimax_decision(tmp_game_matrix, player, Depth_Controller(i));
            if (Agentmove == NULL)
            {
                printf("\nError: Agent No Move found");
            }
            else
            {
                printf("\nai choose move :(%d,%d)", Agentmove->x, Agentmove->y);
                game->move(game, Agentmove);
                free(Agentmove);
            }
        }
        else
        {

            printf("\nRamdom player Choosing move ..");
            struct MSet *avaible_actions = find_possible_moves(game->game_matrix, -player);
            struct msnode *current = avaible_actions->head;
            // choosing random move :
            srand(time(NULL));
            int random_index = rand() % avaible_actions->size;
            for (int i = 0; i < random_index && current->next != NULL; i++)
            {
                current = current->next;
            }
            // getting the chhosen move :
            if (current != NULL)
            {
                move.x = (current->value)->x;
                move.y = (current->value)->y;

                if (move.x == -1 || move.y == -1)
                {
                    printf("\nERROR : Random Player Can Not Choose a Random Move");
                }
                else
                {
                    // perfforming the move :
                    game->move(game, &move);
                }
            }

            // free memory :
            avaible_actions->free(avaible_actions);
            free(avaible_actions);
        }

        game->count(game);
        check_winner(game);
        game->next(game);

        /*           #ifdef _WIN32
              system("cls");  // Windows
          #else
              system("clear");  // Linux/macOS
          #endif */

        i++;
    }

    if (!Quit)
    {
        check_winner(game);
        game->print(game);
        char winner[15];
        (game->winner == W) ? strcpy(winner, "white") : strcpy(winner, "Black");
        printf(ANSI_COLOR_BLUE "\n%s player win" ANSI_RESET, winner);
    }
    else
    {
        printf("Quitting Game\n");
    }
    int winner = game->winner;
    free(game);
    return winner;
}