#include "player/physics.h"
#include "world/staircase.h"

#include <stdio.h>

#define DIFFERENCE 2.0f /* magic! :) */

/* this code is about to give me a mental breakdown
 * maybe future me can figure it out.
 
 * it works but not how i want it to */
float move_down__(float y_pos, Camera3D camera){
  stair_t* stairs = get_stairs_z();
  if(y_pos == 2.0f &&
    (camera.position.x >= stairs[0].dimensions.x)) return NO;
  // TODO: look thru X positions
  // for now we're doing Z positions, as a "proof of concept"
  
  for(int j = 0; j != stairs_z_index; j++){
    if(y_pos == stairs[j].y_pos){
      // matched:)
      printf("gottem! (%.2f == %.2f)\n",
             y_pos, stairs[j].y_pos);
      
      // should i kill myself
      camera.position.y = stairs[j].y_pos;
      
      return YES;
      break;
    }
    else {
      continue;
    }
  }

  // DEFAULT -- No matches given, so we
  // don't move down
  return NO;
}