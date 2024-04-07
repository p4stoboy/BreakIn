#pragma once

#include "types.h"

// bullet effect functions
bool bullet_standard(Bullet& b, ivec2 grid_pos, GameState& g);
bool bullet_explosion(Bullet& b, ivec2 grid_pos, GameState& g);
bool bullet_acid(Bullet& b, ivec2 grid_pos, GameState& g);

// util
Bullet roll_bullet();
