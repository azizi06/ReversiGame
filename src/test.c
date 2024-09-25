
#include <stdio.h>
#define ROWS 8
#define COLUMNS 8
int print_matrix(int matrix[ROWS][COLUMNS]){
    printf("\n");
    for(int i = 0; i < ROWS;i++){
    for(int j = 0; j < COLUMNS;j++){
        printf("  %d  ", matrix[i][j]);

    }
    printf("\n");

    }
}
int b(int arr[ROWS][COLUMNS]){
    printf("arr 1 :");
    print_matrix(arr);
}
int main(){
    int arr[ROWS][COLUMNS] = {0};
    int arr2[ROWS][COLUMNS] = {1,1,1,1,1,1,1,1,1,1};
    b(arr);
    //printf("arr2");
    //print_matrix(arr2);

}