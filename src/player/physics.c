#include "player/physics.h"
#include "world/staircase.h"

#include <stdio.h>

#define DIFFERENCE 2.0f /* magic! :) */

/* this code is about to give me a mental breakdown
 * maybe future me can figure it out.
 
 * it works but not how i want it to */
float move_down__(float y_pos, player_t player){
  stair_t* stairs = get_stairs_z();
  // TODO: look thru X positions
  // for now we're doing Z positions, as a "proof of concept"
  
  for(int j = 0; j != stairs_z_index; j++){
    // So basically what we want to do is:
    // -> Check if the Y position of the player is at the stairs' position
    // -> Check if the X position is inside the current stair
    // -> Same for the Z position
    if(y_pos != stairs[j].y_pos){
      // Check for X position
      if(player.position.x >= stairs[j].dimensions.x &&
         player.position.x < (stairs[j].dimensions.x+stairs[j].width)){
          return NO;
      } else continue;
    } else continue;
  }

  // DEFAULT -- No matches given, so we
  // don't move down
  return NO;
}