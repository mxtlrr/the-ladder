#pragma once

#include <raylib.h>

typedef struct {
  float y_pos;
  Vector2 dimensions; /* dimensions.x -> Width
                       * dimensions.y -> Length */
  Color color;
  /* todo -- some more info */
} stair_t;

// Draw a staircase in the Z direction. It uses the starting stair's
// original position, to draw "stair_count" amount of stairs.
//
// The stairs head downwards, and descend by y-=1, z+=1.5
void _drawstaircase_z(stair_t starting_stair, int stair_count);

// The exact same function as above, however this happens:
// y -= 1, z -= 1.5
//
// NOTE: name is a misnomer
void _drawstaircase_x(stair_t starting_stair, int stair_count);