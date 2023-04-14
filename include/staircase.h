#pragma once

#include <raylib.h>

typedef struct {
  float y_pos;
  /* todo -- some more info */
} stair_t;

/* TODOs:
  -> Change return type
  -> Actually write the function */
void _drawstaircase(stair_t* stairs);