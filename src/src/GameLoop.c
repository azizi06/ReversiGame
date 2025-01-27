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
        if (game->player == player)
        { // ai player
            printf("\nai choosing a move...\n");
            int tmp_game_matrix[ROWS][COLUMNS] = {E};
            copy_2d_array(tmp_game_matrix, game->game_matrix);

            struct Move *Agentmove = minimax_decision(tmp_game_matrix, player, Depth_Controller(i));
            if (Agentmove == NULL)
            {
                printf("\nError: MinMax Agent No Move found");
                continue;
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
            struct MSet *available_actions = find_possible_moves(game->game_matrix, -player);
            if (available_actions->size == 0)
            {
                printf("\nRandome Player No Moves Found");
                continue;
            }

            struct msnode *current = available_actions->head;
            // choosing random move :
            srand(time(NULL));
            int random_index = rand() % available_actions->size;
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
                    continue;
                }
                else
                {
                    // perfforming the move :
                    game->move(game, &move);
                }
            }

            // free memory :
            available_actions->free(available_actions);
            free(available_actions);
        }

        game->count(game);
        // game->print(game);

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

int PlayAgainstMinMaxAgent(int player)
{
    struct Reversi *game = new_reversi();
    bool Quit = false;
    int i = 0; // move count;
    char input_x[10];
    char input_y[10];
    char current_player[6]; 
    strcpy(current_player, (player == W) ? "White" : "Black");

    while (!game->isgame_over(game))
    {
        struct Move move = {-1, -1};
        if (game->player == player)
        {
            game->print(game);
            printf( (player == W)? ANSI_COLOR_RED "\nWhite Player Turn " ANSI_RESET :  ANSI_COLOR_GREEN "\nBlack Player Turn " ANSI_RESET);
            if (handel_player_input(game, input_x, input_y) == -1)
            {
                Quit = true;
                break; // Quit the game
            }
            // PERFORMING A MOVE :
            move.x = atoi(input_x);
            move.y = atoi(input_y);
            game->move(game, &move);

           
        }else
        { // ai player
            printf("\nai choosing a move...\n");
            int tmp_game_matrix[ROWS][COLUMNS] = {E};
            copy_2d_array(tmp_game_matrix, game->game_matrix);

            struct Move *Agentmove = minimax_decision(tmp_game_matrix, player, Depth_Controller(i));
            if (Agentmove == NULL)
            {
                printf("\nError: MinMax Agent No Move found");
                continue;
            }
            else
            {
                printf("\nai choose move :(%d,%d)", Agentmove->x, Agentmove->y);
                game->move(game, Agentmove);
                free(Agentmove);
                 game->print(game);
            }
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