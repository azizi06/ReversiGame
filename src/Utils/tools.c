#include "tools.h"
#include<stdio.h>
#include<stdlib.h>
int print_matrix(int matrix[ROWS][COLUMNS]){
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