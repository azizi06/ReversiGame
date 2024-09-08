#include <stdio.h>

#include "raylib.h"
#include "map.h"

int main() {
   
    struct Map *map = map_new(map);
    int m[8][8] = {2};
    int m2[8][8] = {7};
    int m3[8][8] = {9};
    int m4[8][8] = {0};

     map->add(map,m,6);
     map->add(map,m2,1);
     map->add(map,m4,4);
     map->add(map,m3,4);
     //map->add(map,m4,89);
    
     map->print(map);
     

    
   

    return 0;
}

