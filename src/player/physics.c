#include "player/physics.h"

#include <stdio.h>

#define DIFFERENCE 2.0f /* magic! :) */

#ifdef GAP
  #define FIXED_GAP 0.5f
#else
  #define GAP 0.5f
#endif

/* this code is about to give me a mental breakdown
 * maybe future me can figure it out.
 
 * it works but not how i want it to */

int done = 0x0000;
float z_start = -0.487900f;
float z_end   =  0.511940f;

/* Find the start Z position of the stair */
float find_starting_stair(int stair_n, float stair0_pos,
                          float width){
  /* no idea why this works 
    but it odes so i can't complain */
  const float MAGIC_START = 0.49984;
  if(stair_n > 2){
    // stair0 pos is the original starting position of the first stair
    //
    // basically:
    // ((stair0+width)-0.49984)+0.5 gives stair 1's initial position
    // if we use stair 1's position in place of stair 0, we should
    // theoretically get stair 2's position.
    float stair_0 =((stair0_pos+width)-MAGIC_START)+FIXED_GAP;
    float new = 0.0f;
    float stair__n = stair_0;
    for(int i = 0; i != stair_n+1; i++){
      stair__n = ((stair__n+width)-MAGIC_START)+FIXED_GAP;
      new = stair__n;
      /* new = stair_n */

    }
    return new-1.0f;
  } else {
    // i need to come up with something new
  }
}


float move_down__(float y_pos, player_t player, stair_t starting,
                  Camera camera){
  float len = z_end-z_start; // 0.99984
  float starting_ = z_start+0.487900; // where stair 0 starts

  stair_t* stairs = get_stairs_z();

  // now we can calculate where step 1 can be
  /* Add the starting position of stair 0 to it's width,
     Followed by the gap between stairs. */
  printf("%.6f\n", ((starting_+len)-0.49984)+FIXED_GAP);
  printf("test: %.6f\n", find_starting_stair(0, (z_start+0.487900), len));
  
  float stair0pos = ((starting_+len)-0.49984)+FIXED_GAP;
  float stair1pos = ((stair0pos+len)-0.49984)+FIXED_GAP;
  printf("%.6f\n", stair1pos);

  // printf("stair 0 starts at %.6f (reality=%.6f)\n",
  //       starting_, stairs[0].dimensions.y/*-0.2*/);
  // printf("Place where step 1 should be: %.6f (reality is %.6f)\n",
  //       step_1, stairs[1].dimensions.y);

 
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