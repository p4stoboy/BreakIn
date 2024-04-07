#pragma once

#include "types.h"
#include "types.h"
#include <vector>

//GLOBAL
void update_global_state(GameState& g);


// BLOCK
void block_update(Block& b, GameState& g);
void block_draw(Block& b);
void block_destroy(Block& b, GameState& g);


//BULLET
void bullet_update(Bullet& b, GameState& g);
void bullet_destroy(Bullet& b, GameState& g);
void bullet_draw(Bullet& b);
void bullet_check_wall_collision(Bullet& b);
void bullet_check_block_collision(Bullet& b, GameState& g);
void bullet_check_paddle_collision(Bullet& b, GameState& g);
void trail_update(Bullet& b);
void trail_draw(Bullet& b);

void update_bullets(GameState& g);
void draw_bullets(GameState& g);


// PADDLE
void paddle_update(GameState& g);
void paddle_draw(GameState& g);


// PARTICLE
void particle_update(Particle& p);
void particle_draw(Particle& p);

void update_particles(GameState& g);
void draw_particles(GameState& g);


// TERRAIN
int count_non_empty_rows(GameState& g);
void shift_rows_down(GameState& g, int num_rows_to_shift);
void add_new_chunk(GameState& g, int num_rows, std::function<Grid(int, int)> pattern_func);
void update_terrain(GameState& g);
void draw_terrain(GameState& g);
void deactivate_disconnected_clusters(GameState& g);
void dfs_mark_reachable(GameState& g, int row, int col, std::vector<std::vector<bool>>& visited);
