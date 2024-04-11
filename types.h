#pragma once

#include <memory>
#include <vector>
#include "splashkit.h"
#include <functional>

struct ivec2;
struct GameState;
struct Paddle;
struct Ball;
struct Block;
struct Particle;


using Row = std::vector<std::unique_ptr<Block>>;
using Grid = std::vector<Row>;
using BallEffect = bool (*)(Ball& ball, ivec2 grid_pos, GameState& game);
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

struct Ball {
    point_2d pos;
    vector_2d vel;
    int size;
    color clr;
    BallEffect effect;
    bool active;
    std::vector<Particle> trail;
    int ttl_type; // 0 = none, 1 = # hits, 2 = # updates
    int ttl;
    int max_ttl;
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

struct PowerUp {
    point_2d pos;
    vector_2d vel;
    int size;
    color clr;
    bool active;
    std::vector<Particle> trail;
};

struct GameState {
    GameStatus status;
    int score;
    Grid terrain;
    std::vector<Ball> balls;
    std::vector<Particle> particles;
    Paddle paddle;
};
