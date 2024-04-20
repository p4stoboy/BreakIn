#include "include/globals.h"
#include "include/state_init.h"

GameState new_game_state() {
    GameState game;
    game.score = 0;
    game.status = PLAYING;
    game.terrain;
    game.paddle = new_paddle();
    game.balls = {};
    game.particles = {};
    return game;
}

void reset_game_state(GameState& game) {
    game.score = 0;
    game.status = PLAYING;
    game.terrain.clear();
    game.paddle = new_paddle();
    game.balls = {};
    game.particles = {};
}

Paddle new_paddle() {
    Paddle paddle;
    paddle.x = WINDOW_WIDTH / 2;
    paddle.y = WINDOW_HEIGHT - 50;
    paddle.width = 100;
    paddle.height = 10;
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

Ball new_ball(point_2d pos, vector_2d vel, int size, color clr, BallEffect effect, int ttl_type, int ttl) {
    Ball ball;
    ball.pos = pos;
    ball.vel = vel;
    ball.size = size;
    ball.clr = clr;
    ball.effect = effect;
    ball.active = true;
    ball.trail = {};
    ball.ttl_type = ttl_type;
    ball.ttl = ttl;
    ball.max_ttl = ttl;
    return ball;
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

