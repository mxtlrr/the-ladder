#include "staircase.h"

void _drawstaircase_z(stair_t starting_stair, int stair_count){
  Vector3 pos = (Vector3){starting_stair.dimensions.x,
                          starting_stair.y_pos,
                          starting_stair.dimensions.y /* see staircase.h */ };

  for(int i = 0; i != stair_count+1; i++){
    DrawPlane((Vector3){pos.x, pos.y, pos.z}, 
          (Vector2){10.0f, 1.0f},           /* do not change */
          starting_stair.color);

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

    // update values
    pos.y = pos.y - 1.0f;
    pos.z -= 1.5f;
  }
}

