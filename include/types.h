#pragma once

#include <memory>
#include <vector>
#include "splashkit/splashkit.h"
#include <functional>

struct ivec2;
struct GameState;
struct Paddle;
struct Ball;
struct Block;
struct Particle;


/**
 * @brief A Row is a vector of unique pointers to blocks.
 * @details A Row is used to represent a row of blocks in the game.
 */
using Row = std::vector<std::unique_ptr<Block>>;

/**
 * @brief A Grid is a vector of rows.
 * @details A Grid is used to represent the grid of blocks in the game.
 */
using Grid = std::vector<Row>;

/**
 * @brief A BallEffect is a function pointer that is used to represent the effect of a ball.
 * @details A BallEffect takes a ball, grid position (of the block the ball collided with),
 * and game state as arguments and returns a boolean.
 * The boolean is used immediately after the effect function call in the ball_check_wall_collision (ball_state.cpp) function to determine if the ball should
 * change direction after colliding with a block (or not, like with acid).
 * We are using a raw pointer instead of std::function here as the global ball vector gets resized and we don't
 * want Ball to have to implement move and copy semantics.
 */
using BallEffect = bool (*)(Ball& ball, ivec2 grid_pos, GameState& game);

/**
 * @brief A PatternFunc is a function that is used to generate a pattern of blocks against a Grid.
 * @details A PatternFunc is a function that takes a width and height dimension as arguments and returns a grid.
 * The grid is used to represent the blocks in the game.
 */
using PatternFunc = std::function<Grid(int, int)>;

/**
 * @brief A point_2d is a small struct that is used to represent a point in 2D space.
 * @details A point_2d has an x and y coordinate.
 */
struct ivec2 {
    int x, y;
};

/**
 * @brief A GameStatus is an enum that is used to represent the status of the game.
 * @details A GameStatus can be MENU, PLAYING, or GAME_OVER.
 */
enum GameStatus {
    MENU,
    PLAYING,
    GAME_OVER
};

/**
 * @brief A paddle is a small struct that is used to represent the paddle in the game.
 * @details A paddle has a position, width, height, and color.
 */
struct Paddle {
    int x, y;
    int width;
    int height;
    color clr;
};

/**
 * @brief A particle is a small struct that is used to represent debris in the game.
 * @details A particle has a position, velocity, size, color, time to live, and original size.
 * The time to live is the number of updates the particle will be drawn for before being removed.
 * The original size is used to determine how the particle will shrink over time.
 * The maximum time to live is used to determine how much of the ttl has lapsed to inform other routines (alpha channel etc)
 */
struct Particle {
    point_2d pos;
    vector_2d vel;
    int size;
    color clr;
    int ttl;
    int max_ttl;
    int original_size;
};

/**
 * @brief A ball is a small struct that is used to represent the ball in the game.
 * @details A ball has a position, velocity, size, color, effect, time to live type, time to live, and maximum time to live.
 * The time to live type is used to determine how the ball will be removed from the game.
 * The time to live type can be 0, 1, or 2. 0 means the ball will not be removed, 1 means the ball will be removed after a certain number of hits, and 2 means the ball will be removed after a certain number of updates.
 * The maximum time to live is used to determine how much of the ttl has lapsed to inform other routines (alpha channel etc)
 */
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

/**
 * @brief A block is a small struct that is used to represent the blocks in the game.
 * @details A block has a position, target position, grid position, width, height, color, activity status, and vertical velocity.
 * The target position is used to determine where the block should move to.
 * The target position is just used when the block is due to fall to a new grid position instead of updating instantly.
 * The grid position is used to determine where the block is in the grid (mappable to target pos).
 * The vertical velocity is used to determine how fast the block should move (set to 0 when pos == target_pos).
 */
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

/**
 * @brief A powerup is a small struct that is used to represent the powerups in the game.
 * @details A powerup has a position, velocity, size, color, activity status, and trail.
 * The trail is a vector of particles that is used to represent the trail of the powerup.
 */
struct PowerUp {
    point_2d pos;
    vector_2d vel;
    int size;
    color clr;
    bool active;
    std::vector<Particle> trail;
};

/**
 * @brief A game state is a small struct that is used to represent the state of the game.
 * @details A game state has a game status, score, terrain, balls, particles, and paddle.
 * The game status is used to determine what state the game is in.
 * The score is used to determine the player's score.
 * The terrain is a grid of blocks that is used to represent the blocks in the game.
 * The balls is a vector of balls that is used to represent the balls in the game.
 * The particles is a vector of particles that is used to represent the particles in the game.
 * The paddle is used to represent the paddle in the game.
 */
struct GameState {
    GameStatus status;
    int score;
    Grid terrain;
    std::vector<Ball> balls;
    std::vector<Particle> particles;
    Paddle paddle;
};
