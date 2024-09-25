#include <stdio.h>
#include "GameLoop.h"
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>



// Function prototypes

int main() {
    
  /*    char input[2];
    srand(time(NULL));
    printf("1 - to play with ai \n2 - 2 players game \n3 - Two Bots game   \n4 - train Ai     \nEnter your choice : ");
    fgets(input,sizeof(input),stdin);
    int player = atoi(input);
    switch (player){
    case  1:
        playWithAI();
        break;
    case  2:
        playTwoPlayerGame();
        break;
    case  3:
        twoBotsgame();
        break;
    case  4:
        struct Solver* ai= trainAI(1);
        ai->free(ai);
        break;
    default:
        printf("wrong input\n");
        break;
    }  */
   
  /*  struct Map* map = new_map();
   int m1[ROWS][COLUMNS] = {3,4,5};
   int m2[ROWS][COLUMNS] = {3,2,2,2};
   int m3[ROWS][COLUMNS] = {445,400,5};
   int m4[ROWS][COLUMNS] = {12,54,98};
   int m5[ROWS][COLUMNS] = {92,234,10035};
   int m6[ROWS][COLUMNS] = {453,114,677};
   
   map->add(map,m1,3,4,8.98);
   map->add(map,m2,0,1,7);
   map->add(map,m3,7,8,9.4);
   map->add(map,m4,2,2,43);
   map->add(map,m5,6,4,44);
   map->add(map,m6,3,5,4.2);

   print_map(map);
   free_map(map);
    free(map);
 */
/* struct Solver* ai= trainAI(1);
       // ai->free(ai);
    free_map(ai->q);
    free(ai);
printf("\nhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n"); */
  playWithAI();
    return 0;
}



