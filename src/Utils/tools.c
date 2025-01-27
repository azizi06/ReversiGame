#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reversi.h"
int (*allocate_matrix(int rows, int cols))[COLUMNS]
{
    // Allocate memory for rows
    int(*matrix)[COLUMNS] = malloc(rows * sizeof(*matrix));

    // Check for successful allocation
    if (matrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLUMNS; j++)
        {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void free_matrix(int (*matrix)[COLUMNS])
{
    free(matrix);
}

int print_matrix(int matrix[ROWS][COLUMNS])
{
    printf("\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            printf("  %d  ", matrix[i][j]);
        }
        printf("\n");
    }
}
int compare_2d_array(int arr1[ROWS][COLUMNS], int arr2[ROWS][COLUMNS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (arr1[i][j] != arr2[i][j])
            {
                return 0; // Arrays are not equal
            }
        }
    }
    return 1; // Arrays are equal
}
struct MSet *point_neighbors(int matrix[ROWS][COLUMNS], struct Move *move, int player)
{
    struct MSet *neighbors = new_mset();
    int x = move->x;
    int y = move->y;
    int target = (player == W) ? B : W;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            int n_x = x + i;
            int n_y = y + i;
            if ((n_x < ROWS && n_y < COLUMNS) && (n_x >= 0 && n_y >= 0))
            {
                if (matrix[n_x][n_y] == target)
                {
                    printf("\ttarget  : %d,player : %d", target, player);
                    neighbors->append(neighbors, new_move(n_x, n_y));
                }
            }
        }
    }

    return neighbors;
}
int get_input(char *prompt, char *input_buffer, size_t buffer_size)
{
    printf("%s", prompt);
    fgets(input_buffer, buffer_size, stdin);
    if (strncmp(input_buffer, "q", 1) == 0)
    {
        printf("Quitting Game\n");
        return -1; // Indicates that we should quit the game
    }
    input_buffer[strcspn(input_buffer, "\n")] = '\0';
    return 0;
}

int handel_player_input(struct Reversi *self, char *input_x, char *input_y)
{
    int row, col;
    while (true)
    {
        if (get_input("\nEnter Row : ", input_x, sizeof(input_x)) == -1)
        {
            return -1; // Quit the game
        }
        if (get_input("Enter Col : ", input_y, sizeof(input_y)) == -1)
        {
            return -1; // Quit the game
        }
        row = atoi(input_x);
        col = atoi(input_y);

        if (is_correct_input(self, row, col, self->player))
        {
            break;
        }
        else
        {
            printf("Invalid input. Please try again.\n");
        }
    }
    // success
    return 0;
}
void copy_2d_array(int destination[ROWS][COLUMNS], int origine[ROWS][COLUMNS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            destination[i][j] = origine[i][j];
        }
    }
}
int **allocate2DArray()
{
    int rows = ROWS;
    int columns = COLUMNS;
    int *data = (int *)malloc(rows * columns * sizeof(int)); // Single block allocation
    int **array = (int **)malloc(rows * sizeof(int *));      // Array of row pointers

    for (int i = 0; i < rows; i++)
    {
        array[i] = &data[i * columns]; // Assign pointers to each row
    }

    return array;
}

int choose_random(float p)
{
    // Generate a random float between 0 and 1
    float r = (float)rand() / RAND_MAX;

    // Return 1 with probability p, 0 otherwise
    return r < p ? 1 : 0;
}
void **free2DArray(int **array)
{
    for (int i = 0; i < ROWS; i++)
    {
        free(array[i]);
    }
    free(array);
}
void print_board(int board[ROWS][COLUMNS]){
    for(int i = 0;i<COLUMNS;i++){
        printf("%d ",i);
    }

    for(int i=0;i<ROWS;i++){
        printf("\n %d  ",i);
        for(int j=0;j<COLUMNS;j++){
            int value ;
                value = board[i][j];
            
            switch (value)
            {
            case W:
                printf(ANSI_COLOR_RED"W "ANSI_RESET);
                break;
            case B:
                printf(ANSI_COLOR_GREEN"B "ANSI_RESET);
                break;
            case P:
                printf(ANSI_COLOR_BLUE"P "ANSI_RESET);
                break;
            default:
                printf("# ");
                break;
            }
        }
}}
