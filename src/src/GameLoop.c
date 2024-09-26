#include "GameLoop.h"
#include "reversi.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"
#include "tools.h"
#include "minmax.h"
void playWithAI();
void playTwoPlayerGame();
struct Solver *trainAI(int n);
void update_ai(struct Solver *self, int old_state[COLUMNS][ROWS], struct Move *action, int new_state[COLUMNS][ROWS], float reward);

void playWithAI()
{
    struct Reversi *game = new_reversi();
    struct Solver *ai = trainAI(10000);
    char input_x[10];
    char input_y[10];
    bool Quit = false;
    struct Move move;
    ai->player = W;
    while (!game->isgame_over(game))
    {
        game->print(game);

        if (game->player == W)
        {
            printf(ANSI_COLOR_RED "\nWhite Player Turn " ANSI_RESET);
            struct Move *ai_move = NULL;
            int attemps = 5;
            while (ai_move == NULL && attemps > 0)
            {
                ai_move = ai_choose_move(ai, game->game_matrix);
                printf("\n[%d]ai choosing move...", attemps);
                attemps--;
            }
            game->move(game, ai_move);
            printf("\nai choose move (%d,%d)", ai_move->x, ai_move->y);
            free(ai_move);
        }
        else
        {
            printf(ANSI_COLOR_GREEN "\nBlack Player Turn " ANSI_RESET);
            if (handel_player_input(game, input_x, input_y) == -1)
            {
                Quit = true;
                break; // Quit the game
            }
            // PERFORMING A MOVE :
            move.x = atoi(input_x);
            move.y = atoi(input_y);
            game->move(game, &move);
        }
        game->count(game);
        // Switching Player
        check_winner(game);
        game->next(game);
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
    free(game);
    free_map(ai->q);
    free(ai);
}
void playTwoPlayerGame()
{
    srand(time(NULL));
    int random = rand() % 2;
    char input_x[10];
    char input_y[10];
    struct Move move;
    struct Reversi *game = new_reversi();
    bool Quit = false;
    while (!game->isgame_over(game))
    {
        // print game to the screen :
        game->print(game);
        int Player = game->player;
        // reading input :
        if (Player == B)
        {
            printf(ANSI_COLOR_GREEN "\nBlack Player Turn " ANSI_RESET);
        }
        else
        {
            printf(ANSI_COLOR_RED "\nWhite Player Turn " ANSI_RESET);
        }
        if (handel_player_input(game, input_x, input_y) == -1)
        {
            Quit = true;
            break; // Quit the game
        }
        // PERFORMING A MOVE :
        move.x = atoi(input_x);
        move.y = atoi(input_y);
        game->move(game, &move);
        // counting score
        game->count(game);
        // Switching Player
        game->next(game);
    }
    if (!Quit)
    {
        check_winner(game);
        game->print(game);
        char winner[15];
        (game->winner == W) ? strcpy(winner, "white") : strcpy(winner, "Black");
        printf(ANSI_COLOR_BLUE "\n%s player win" ANSI_RESET, winner);
    }
}
void twoBotsgame()
{
    struct Reversi *game = new_reversi();
    struct Solver *ai_w = new_solver(0.5, 0.5, W);
    struct Solver *ai_b = new_solver(0.5, 0.5, B);
    bool Quit = false;

    while (!game->isgame_over(game))
    {
        game->print(game);

        if (game->player == W)
        {
            printf(ANSI_COLOR_RED "\nWhite Player Turn " ANSI_RESET);
            struct Move *move = NULL;
            int attemps = 5;
            while (move == NULL && attemps > 0)
            {
                move = ai_choose_move(ai_w, game->game_matrix);
                printf("\n[%d]ai_w choosing move...", attemps);
                attemps--;
            }
            game->move(game, move);
            printf("\nai choose move (%d,%d)", move->x, move->y);
            free(move);
        }
        else
        {
            printf(ANSI_COLOR_RED "\nWhite Player Turn " ANSI_RESET);
            struct Move *move = NULL;
            int attemps = 5;
            while (move == NULL && attemps > 0)
            {
                move = ai_choose_move(ai_b, game->game_matrix);
                printf("\n[%d]ai_b choosing move...", attemps);
                attemps--;
            }
            game->move(game, move);
            printf("\nai choose move (%d,%d)", move->x, move->y);
            free(move);
        }
        game->count(game);
        // Switching Player
        game->next(game);
    }
    if (!Quit)
    {
        check_winner(game);
        game->print(game);
        char winner[15];
        (game->score_w > game->score_b) ? strcpy(winner, "white") : strcpy(winner, "Black");
        printf(ANSI_COLOR_BLUE "\n%s player win" ANSI_RESET, winner);
    }
    else
    {
        printf("Quitting Game\n");
    }

    free_map(ai_w->q);
    free_map(ai_b->q);
    free(ai_w);
    free(ai_b);
    free(game);
}

struct Solver *trainAI(int n)
{
    struct Solver *ai = new_solver(0.5, 1, B);

    bool Quit = false;
    for (int i = 0; i < n; i++)
    {
        printf("\nTraining ai game %d  ", i);
        struct Reversi *game = new_reversi();
        bool runing = true;
        while (runing)
        {
            // game->print(game);
            ai->player = game->player;

            // int (*old_state)[COLUMNS] = allocate_matrix(ROWS, COLUMNS);
            int old_state[ROWS][COLUMNS] = {0};
            copy_2d_array(old_state, game->game_matrix);
            // print_matrix(old_state);

            struct Move *move = ai_choose_move(ai, game->game_matrix);
            if (move == NULL)
            {
                break;
            }

            game->move(game, move);

            // int (*new_state)[COLUMNS] =allocate_matrix(ROWS, COLUMNS);;
            int new_state[ROWS][COLUMNS] = {0};

            copy_2d_array(new_state, game->game_matrix);
            game->count(game);
            game->next(game);

            if (game->isgame_over(game))
            {

                check_winner(game);
                if (ai->player == game->winner)
                {
                    // update_ai(ai, old_state, move, new_state, 1);
                }
                else
                {
                    // update_ai(ai, old_state, move, new_state, -1);
                }

                runing = false;
                // free_matrix(old_state);
                // free_matrix(new_state);
                free(move);
                break;
            }
            else
            {

                // update_ai(ai, old_state, move, new_state, 0);
            }

            free(move);
            // free_matrix(old_state);
            // free_matrix(new_state);
        }
        printf("   The winner is %d", game->winner);

        free(game);
    }
    printf("\nheeeeeeeeeeeeee");
    return ai;
}
void update_ai(struct Solver *self, int old_state[COLUMNS][ROWS], struct Move *action, int new_state[COLUMNS][ROWS], float reward)
{
    float old_q;
    float bf_reward = 0;
    struct Map *map_get = self->q;
    struct Map *map_add = self->q;

    float *old = NULL; // get_value(map_get, old_state, action);
    if (old == NULL)
    {
        old_q = 0;
    }
    else
    {
        old_q = *old;
    }

    float best_future = best_future_reward(self, new_state);

    bf_reward = best_future;

    float new_value = old_q + (self->alpha) * ((reward + bf_reward) - old_q);
    int arr[ROWS][COLUMNS] = {9999, 444, 44, 4, 4};
    int x = action->x;
    int y = action->y;
    // printf("\nx : %d  , y :%d",x,y);
    add_node(map_add, old_state, x, y, new_value);
    // print_map(self->q);
    // update_q_value(self, old_state, action, old_q, reward, bf_reward);
}
void playWihtMinMaxAgent()
{
    struct Reversi *game = new_reversi();
    int player = B;
    char input_x[10];
    char input_y[10];
    bool Quit = false;
    struct Move move;
    while (!game->isgame_over(game))
    {
        game->print(game);
        if (game->player == player)
        {

            if (handel_player_input(game, input_x, input_y) == -1)
            {
                Quit = true;
                break; // Quit the game
            }
            // PERFORMING A MOVE :
            move.x = atoi(input_x);
            move.y = atoi(input_y);
            game->move(game, &move);
        }
        else
        {
            printf("\nai choosing a move...\n");

            struct Move *Agentmove = best_move(game->game_matrix, game->player);
            if (Agentmove == NULL)
            {
                printf("Error No Move not fount");
                break;
            }
            printf("\nai choose move :(%d,%d)", Agentmove->x, Agentmove->y);
            game->move(game, Agentmove);
            free(Agentmove);
        }
        game->count(game);
        // Switching Player
        check_winner(game);
        game->next(game);
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

    free(game);
}
void RandomPlayerWihtMinMaxAgent()
{
    struct Reversi *game = new_reversi();
    int player = B;
    char input_x[10];
    char input_y[10];
    bool Quit = false;
    struct Move move = {-1,-1};
    while (!game->isgame_over(game))
    {
        game->print(game);
        if (game->player == player)
        {
            struct MSet *avaible_actions = find_possible_moves(game->game_matrix, game->player);
            struct msnode *current = avaible_actions->head;
            int random_index = rand() % avaible_actions->size;
            for (int i = 0; i < random_index && current != NULL; i++)
            {
                current = current->next;
            }
            if (current != NULL)
            {
                move.x = (current->value)->x;
                move.y = (current->value)->y;
            }
            if(move.x == -1 || move.y == -1){
                printf("ERROR : Random Player Can Not Choose a Random Move");
                return;
            }
            game->move(game, &move);
        }
        else
        {
            printf("\nai choosing a move...\n");

            struct Move *Agentmove = best_move(game->game_matrix, game->player);
            if (Agentmove == NULL)
            {
                printf("Error: Agent No Move not found");
                return;
            
            }
            printf("\nai choose move :(%d,%d)", Agentmove->x, Agentmove->y);
            game->move(game, Agentmove);
            free(Agentmove);
        }
        game->count(game);
        // Switching Player
        check_winner(game);
        game->next(game);
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

    free(game);
}