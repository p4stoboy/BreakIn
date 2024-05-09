#include "types.h"


/**
 * @brief Draw the block.
 *
 * @param b The block to draw.
 */
void block_draw(const Block& b);

/**
 * @brief Draw the terrain in the game.
 *
 * @param g The game state.
 */
void draw_terrain(GameState& g);



/**
 * @brief Draw the ball.
 *
 * @param b The ball to draw.
 */
void ball_draw(Ball& b);

/**
 * @brief Draw the balls in the game.
 *
 * @param g The game state.
 */
void draw_balls(GameState& g);

/**
 * @brief Draw the ball's trail.
 *
 * @param b The ball to draw the trail for.
 */
void trail_draw(Ball& b);



/**
 * @brief Draw the paddle.
 *
 * @param g The game state.
 */
void paddle_draw(GameState& g);



/**
 * @brief Draw the particle.
 *
 * @param p The particle to draw.
 */
void particle_draw(Particle& p);

/**
 * @brief Draw the particles in the game.
 *
 * @param g The game state.
 */
void draw_particles(GameState& g);
