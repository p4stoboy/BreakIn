#pragma once

#include "types.h"

GameState new_game_state();
void reset_game_state(GameState& game);
Paddle new_paddle();
Particle new_particle(point_2d pos, vector_2d vel, color clr, int size, int ttl);
Bullet new_bullet(point_2d pos, vector_2d vel, int size, color clr, BulletEffect effect, int ttl_type, int ttl);
Block new_block(point_2d pos, point_2d target_pos, ivec2 grid_pos, int width, int height, color c);
