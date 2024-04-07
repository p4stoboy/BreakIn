#pragma once

#include "splashkit.h"
#include "XOR.h"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int WINDOW_OFFSET;
extern int TERRAIN_OFFSET;
extern int TERRAIN_WIDTH;
extern int TERRAIN_HEIGHT;
extern int SCREEN_START;
extern int SCREEN_END;
extern int NUM_ROWS;
extern int NUM_COLS;
extern int BLOCK_WIDTH;
extern int BLOCK_HEIGHT;
extern float BLOCK_POWERUP_CHANCE;
extern int MAX_PADDLE_WIDTH;
extern int MIN_PADDLE_WIDTH;

// screen shake
extern int SSX;
extern int SSY;

// rng
extern XOR rng;

extern color clr_background;
extern color clr_paddle;
extern color clr_block;
extern color clr_bullet_standard;
extern color clr_bullet_explosion;
extern color clr_bullet_acid;

