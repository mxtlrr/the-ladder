#pragma once

#include <raylib.h>

// The raylib camera uses these values to move the camera up or down.
// -1.0f -- down
// 0.0f  -- neither
// 1.0f  -- up
#define YES -1.0f
#define NO  0.0f

/* Should the player move down, depending on it's current Y position? */
float move_down__(float y_pos, Camera3D camera);