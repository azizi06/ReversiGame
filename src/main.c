#include <stdio.h>

#include "raylib.h"
#include "map.h"
#include "set.h"

int main() {
   
   int m[ROWS][COLUMNS] = {0};
   int m2[ROWS][COLUMNS] = {2};
   int m3[ROWS][COLUMNS] = {3};
   int m4[ROWS][COLUMNS] = {4};

   struct Set* set =new_set();
   set->append(set,m);
   
   set->append(set,m);
   set->append(set,m2);
   set->append(set,m4);
   set->append(set,m3);

   printf("\nhoooooo");
   
   bool f = set->exists(set,m4);
   if(f){
      printf("\nm4 exists");
   }else{
      printf("m3 do not exists");
   }

   set->print(set);
   
   printf("\n-----------------------------------");
   delete_snode(set,m);
   set->print(set);
  

    
   

    return 0;
}

