#include "player/physics.h"

#include <stdio.h>

#define DIFFERENCE 2.0f /* magic! :) */

/* this code is about to give me a mental breakdown
 * maybe future me can figure it out.
 
 * it works but not how i want it to */

int done = 0x0000;
float z_start = -0.487900f;
float z_end   =  0.511940f;


float move_down__(float y_pos, player_t player, stair_t starting,
                  Camera camera){
  float len = z_end-z_start; // 0.99984
  stair_t* stairs = get_stairs_z();

  /* this is a horrible way to do it */
  // printf("stair 1 should be at (z=%.6f), width in z is %.6f.\n",
  //        (0.0f+len-1.48774)*-4.074, len);
  // printf("reality: (z=%.6f), width in z is %.6f.\n",
  //        stairs[2].dimensions.y+0.4879, stairs[2].width-0.00016);

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
    // -> Check if the Y position of the player is at the stairs' position (1)
    // -> Check if the X position is inside the current stair (2)
    // -> Same for the Z position (3)

    // (1)
    if(y_pos == stairs[j].y_pos+2){

      // We are in betwen the current stair.
      // (2)
      if(camera.position.x <= STARTING_AT &&
         camera.position.x >= ENDING_AT){
        printf("HOLY SHIT YES!\n");
        // (3)
        
        return YES;
      }
    } else {
      return NO;
    }
  }

  // DEFAULT -- No matches given, so we
  // don't move down
  return NO;
}