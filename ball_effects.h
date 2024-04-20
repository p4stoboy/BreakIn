#pragma once

#include "types.h"

// ball effect functions
/**
 * @brief Ball effect function that is used to represent the effect of a ball when
 * ball collides with Block.
 *
 * @param b The ball.
 * @param grid_pos The grid position of collided Block.
 * @param g The game state.
 * @return true If ball should rebound.
 * @return false If ball should continue on same trajectory.
 */
bool ball_standard(Ball& b, ivec2 grid_pos, GameState& g);
bool ball_explosion(Ball& b, ivec2 grid_pos, GameState& g);
bool ball_acid(Ball& b, ivec2 grid_pos, GameState& g);

// util
/**
 * @brief Generate a ball with a randomly selected effect.
 *
 * @return Ball The generated ball.
 */
Ball roll_ball();
