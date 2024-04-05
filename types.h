#pragma once

#include <memory>
#include <vector>
#include "splashkit.h"
#include <functional>

struct ivec2;
struct GameState;
struct Paddle;
struct Bullet;
struct Block;
struct Particle;


using Row = std::vector<std::unique_ptr<Block>>;
using Grid = std::vector<Row>;
using PowerUp = bool (*)(Bullet& bullet, ivec2 grid_pos, GameState& game);
using PatternFunc = std::function<Grid(int, int)>;

struct ivec2 {
    int x, y;
};

enum GameStatus {
    MENU,
    PLAYING,
    GAME_OVER
};

struct Paddle {
    int x, y;
    int width;
    color clr;
};

struct Particle {
    point_2d pos;
    vector_2d vel;
    int size;
    color clr;
    int ttl;
    int max_ttl;
    int original_size;
};

struct Bullet {
    point_2d pos;
    vector_2d vel;
    int size;
    color clr;
    PowerUp powerup;
    bool active;
    std::vector<Particle> trail;
};

struct Block {
    point_2d pos;
    point_2d target_pos;
    ivec2 grid_pos;
    int width;
    int height;
    color clr;
    bool active;
    float y_vel;
};

struct GameState {
    GameStatus status;
    Grid terrain;
    std::vector<Bullet> bullets;
    std::vector<Particle> particles;
    Paddle paddle;
};
