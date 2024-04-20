#pragma once

#include "splashkit.h"
#include "XOR.h"

/**
 * @brief The global window dimensions.
 *
 */
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

/**
 * @brief The global game area dimensions.
 *
 */
extern const int GAME_AREA_OFFSET;
extern const int GAME_AREA_WIDTH;
extern const int GAME_AREA_HEIGHT;
extern const int GAME_AREA_START;
extern const int GAME_AREA_END;

/**
 * @brief The global terrain dimensions and offsets relative to window.
 *
 */
extern const int TERRAIN_OFFSET;
extern const int TERRAIN_WIDTH;
extern const int TERRAIN_HEIGHT;

/**
 * @brief Terrain dimensions
 *
 */
extern const int NUM_ROWS;
extern const int NUM_COLS;

/**
 * @brief The global block dimensions inside the Terrain Grid.
 *
 */
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
/**
 * @brief The global random number generator.
 *
 */
extern XOR rng;

/**
 * @brief The game palette.
 *
 */
extern const color clr_background;
extern const color clr_paddle;
extern const color clr_block;
extern const color clr_ball_standard;
extern const color clr_ball_explosion;
extern const color clr_ball_acid;

