#include "world/staircase.h"
#include <stdio.h>

// SOON/TODO: bi.g
stair_t stairs_z[10];
stair_t stairs_x[10];

stair_t* get_stairs_x(){ return stairs_x; }
stair_t* get_stairs_z(){ return stairs_z; }

int stairs_z_index = 0;
int stairs_x_index = 0;

void _drawstaircase_z(stair_t starting_stair, int stair_count){
  Vector3 pos = (Vector3){starting_stair.dimensions.x,
                          starting_stair.y_pos,
                          starting_stair.dimensions.y /* see staircase.h */ };

  for(int i = 0; i != stair_count+1; i++){
    DrawCube((Vector3){pos.x, pos.y, pos.z}, WIDTH_STAIR,
             0.1f, LENGTH_STAIR, starting_stair.color);


    // before we update, lets add to the array
    stair_t cur_stair = {
      .color = starting_stair.color,
      .dimensions = (Vector2){pos.x, pos.z},
      .y_pos = pos.y,
      .width = 0.1f /* see below */
    };
    /* the width value is approximately 0.99984, however
     * for our purposes, you should just round up*/
    stairs_z[stairs_z_index] = cur_stair;

    // this fixes a seg fault lmao
    if(stairs_z_index > stair_count);
    else stairs_z_index++;

    // update values
    pos.y = pos.y - 1.0f;
    pos.z += 1.5f;
  }
}

void _drawstaircase_x(stair_t starting_stair, int stair_count){
  Vector3 pos = (Vector3){starting_stair.dimensions.x,
                          starting_stair.y_pos,
                          starting_stair.dimensions.y};

  for(int i = 0; i != stair_count+1; i++){
    DrawPlane((Vector3){pos.x, pos.y, pos.z}, 
          (Vector2){10.0f, 1.0f},
          starting_stair.color);

    stair_t cur_stair = {
      .color = starting_stair.color,
      .dimensions = (Vector2){pos.x, pos.z},
      .y_pos = pos.y
    };
    stairs_x[stairs_x_index] = cur_stair;
    stairs_x_index++;

    // update values
    pos.y = pos.y - 1.0f;
    pos.z -= 1.5f;
  }
}

