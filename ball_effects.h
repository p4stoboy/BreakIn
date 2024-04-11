#pragma once

#include "types.h"

// ball effect functions
bool ball_standard(Ball& b, ivec2 grid_pos, GameState& g);
bool ball_explosion(Ball& b, ivec2 grid_pos, GameState& g);
bool ball_acid(Ball& b, ivec2 grid_pos, GameState& g);

// util
Ball roll_ball();
