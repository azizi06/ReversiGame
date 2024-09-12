#include "tools.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"reversi.h"

int print_matrix(int matrix[ROWS][COLUMNS]){
    printf("\n");
    for(int i = 0; i < ROWS;i++){
    for(int j = 0; j < ROWS;j++){
        printf("  %d  ", matrix[i][j]);

    }
    printf("\n");

    }
}
int compare_2d_array(int arr1[ROWS][COLUMNS], int arr2[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (arr1[i][j] != arr2[i][j]) {
                return 0;  // Arrays are not equal
            }
        }
    }
    return 1;  // Arrays are equal
}
struct MSet* point_neighbors(int matrix[ROWS][COLUMNS],struct Move* move,int player){
    struct MSet* neighbors = new_mset(); 
    int x = move->x;
    int y = move->y;
    int target = (player == W) ? B : W;
 
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if (i == 0 && j == 0) {
                continue;
            }
            int n_x = x+i;
            int n_y = y+i;
            if((n_x <ROWS && n_y<COLUMNS) && (n_x >= 0 && n_y >= 0)  ){  
                if(matrix[n_x][n_y] == target){
                printf("\ttarget  : %d,player : %d",target,player);            
                    neighbors->append(neighbors,new_move(n_x,n_y));
                }

            }
        }
    }
  
    return neighbors;

}
int get_input(char *prompt, char *input_buffer, size_t buffer_size){
    printf("%s",prompt);
    fgets(input_buffer, buffer_size, stdin);
    if (strncmp(input_buffer, "q", 1) == 0) {
        printf("Quitting Game\n");
        return -1;  // Indicates that we should quit the game
    }
    input_buffer[strcspn(input_buffer, "\n")] = '\0';
    return 0;
}

int handel_player_input(struct Reversi* self,char *input_x, char *input_y){
    int row,col;
    while(true){
        if(get_input("\nEnter Row : ",input_x,sizeof(input_x))== -1){
             return -1;//Quit the game
        }
        if(get_input("\nEnter Col : ",input_y,sizeof(input_y))== -1){
             return -1;//Quit the game
        }
        row = atoi(input_x);
        col= atoi(input_y);

        if (is_correct_input(self, row, col, self->player)) {
            break;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }
    //success
    return 0;
}