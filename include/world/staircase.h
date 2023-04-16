#pragma once

#include <raylib.h>

#define WIDTH_STAIR  3.0f
#define LENGTH_STAIR 1.0f

/* FIXME: this should probably not be hardcoded
 * but oh well */

// X pos
#define STARTING_AT -8.50000f
#define ENDING_AT   -11.50000f


// Z pos
extern float z_start;
extern float z_end;


#define GAP 1.5f
typedef struct {
  float y_pos;
  float width;
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

// The function describes exactly what the function does
stair_t* get_stairs_z();
stair_t* get_stairs_x();

extern int stairs_z_index;
extern int stairs_x_index;