#include <stdio.h>

#include "raylib.h"
#include "map.h"
#include "set.h"

int main() {
   
   int m[ROWS][COLUMNS] = {0};
   int m2[ROWS][COLUMNS] = {2};
   int m3[ROWS][COLUMNS] = {3};
   int m4[ROWS][COLUMNS] = {4};

   struct Map* map = new_map();
   map->add(map,m,new_move(3,4),6);
   map->add(map,m2,new_move(10,26),3);
   map->add(map,m3,new_move(36,4),1);
   map->add(map,m4,new_move(3,44),99);
   map->del(map,m2,new_move(10,26));
   map->print(map);

   printf("\n-----------------------------------");

  

    
   

    return 0;
}

