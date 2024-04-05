#pragma once

#include "types.h"
#include "values.h"
#include "util.h"
#include <vector>

GameState new_game_state();
void reset_game_state(GameState& game);
Paddle new_paddle();
Particle new_particle(point_2d pos, vector_2d vel, color clr, int size, int ttl);
Bullet new_bullet(point_2d pos, vector_2d vel, int size, color clr, PowerUp powerup);
Block new_block(point_2d pos, point_2d target_pos, ivec2 grid_pos, int width, int height, color c);

GameState new_game_state() {
    GameState game;
    game.status = PLAYING;
    game.terrain;
    game.paddle = new_paddle();
    game.bullets = {};
    game.particles = {};
    return game;
}

void reset_game_state(GameState& game) {
    game.status = PLAYING;
    game.terrain.clear();
    game.paddle = new_paddle();
    game.bullets = {};
    game.particles = {};
}

Paddle new_paddle() {
    Paddle paddle;
    paddle.x = WINDOW_WIDTH / 2;
    paddle.y = WINDOW_HEIGHT - 50;
    paddle.width = 100;
    paddle.clr = clr_paddle;
    return paddle;
}

Particle new_particle(point_2d pos, vector_2d vel, color clr, int size, int ttl) {
    Particle particle;
    particle.pos = pos;
    particle.vel = vel;
    particle.size = size;
    particle.clr = clr;
    particle.ttl = ttl;
    particle.max_ttl = ttl;
    particle.original_size = size;
    return particle;
}

Bullet new_bullet(point_2d pos, vector_2d vel, int size, color clr, PowerUp powerup) {
    Bullet bullet;
    bullet.pos = pos;
    bullet.vel = vel;
    bullet.size = size;
    bullet.clr = clr;
    bullet.powerup = powerup;
    bullet.active = true;
    bullet.trail = {};
    return bullet;
}

Block new_block(point_2d pos, point_2d target_pos, ivec2 grid_pos, int width, int height, color c) {
    Block block;
    block.pos = pos;
    block.target_pos = target_pos;
    block.grid_pos = grid_pos;
    block.width = width;
    block.height = height;
    block.clr = c;
    block.active = true;
    block.y_vel = 0.0;
    return block;
}

