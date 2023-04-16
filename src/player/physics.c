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
      // printf("%.6f <= %.6f || %.6f >= %.6f\n",
      //         camera.position.x, starting.dimensions.x+2.0f,
      //         camera.position.x, (starting.dimensions.x)+starting.width);
      if(camera.position.x <= STARTING_AT &&
         camera.position.x >= ENDING_AT){
        printf("HOLY SHIT YES!\n");
      }
      DrawText(TextFormat("%.6f (z pos=%.6f)", camera.position.x,
            camera.position.z),
            50, 47, 20, WHITE);
      // printf("%.6f vs %.6f\n", camera.position.x, player.position.x);
      continue;
    } else continue;
  }

  // DEFAULT -- No matches given, so we
  // don't move down
  return NO;
}