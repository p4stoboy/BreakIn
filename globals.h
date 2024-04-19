#pragma once

#include "splashkit.h"
#include "XOR.h"

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int GAME_AREA_OFFSET;
extern const int GAME_AREA_WIDTH;
extern const int GAME_AREA_HEIGHT;
extern const int GAME_AREA_START;
extern const int GAME_AREA_END;
extern const int TERRAIN_OFFSET;
extern const int TERRAIN_WIDTH;
extern const int TERRAIN_HEIGHT;
extern const int NUM_ROWS;
extern const int NUM_COLS;
extern const int BLOCK_WIDTH;
extern const int BLOCK_HEIGHT;
extern const float BLOCK_POWERUP_CHANCE;
extern const int INITIAL_PADDLE_WIDTH;
extern const int MAX_PADDLE_WIDTH;
extern const int MIN_PADDLE_WIDTH;

// screen shake
extern int SSX;
extern int SSY;

// rng
extern XOR rng;

extern const color clr_background;
extern const color clr_paddle;
extern const color clr_block;
extern const color clr_ball_standard;
extern const color clr_ball_explosion;
extern const color clr_ball_acid;

