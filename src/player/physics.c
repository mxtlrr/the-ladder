#include "player/physics.h"

#include <stdio.h>

#define DIFFERENCE 2.0f /* magic! :) */

/* this code is about to give me a mental breakdown
 * maybe future me can figure it out.
 
 * it works but not how i want it to */
int done = 0x0000;
float move_down__(float y_pos, player_t player, stair_t starting){
  stair_t* stairs = get_stairs_z();

  if(y_pos == starting.y_pos+2 && /* required! */
    (player.position.x >= starting.dimensions.x &&
     player.position.x < (starting.dimensions.x+starting.width))
     && done != 0xfafa){
    printf("NO!\n");
    done = 0xfafa;
    printf("%x\n", 0xfafa);
    return NO;
  }

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
          if(done == 0xfafa){
            printf("shader 2\n");
            done = 0x0;
            return YES;
            break;
          }
          else continue;
      } else {
        DrawText(TextFormat("%.6f (z pos=%.6f) >= %.6f && %.6f < %.6f\n(j=%d)?\n", player.position.x,
              player.position.z, stairs[j].dimensions.x, stairs[j].dimensions.x+stairs[j].width, j),
              50, 47, 20, WHITE);
        continue;
      }
    } else continue;
  }

  // DEFAULT -- No matches given, so we
  // don't move down
  return NO;
}