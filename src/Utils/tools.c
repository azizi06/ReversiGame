#include "tools.h"
#include<stdio.h>
#include<stdlib.h>
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
