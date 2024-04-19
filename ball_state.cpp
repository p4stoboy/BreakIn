#include "globals.h"
#include "state_management.h"
#include "state_init.h"
#include "splashkit.h"
#include "ball_effects.h"
#include "util.h"


void ball_update(Ball& b, GameState& g) {

    if (b.pos.y > GAME_AREA_HEIGHT) {
        b.active = false;
        b.trail.clear();
        return;
    }

    if (b.ttl_type > 0) {
        if (b.ttl_type == 2) --b.ttl;
        if (b.ttl <= 0) {
            b.active = false;
            b.trail.clear();
            return;
        }
    }

    b.pos.x += b.vel.x;
    b.pos.y += b.vel.y;
    ball_check_wall_collision(b);
    ball_check_block_collision(b, g);
    ball_check_paddle_collision(b, g);
    if (rng.chance(0.25)) {
        float trail_limiter = rng.randomFloat(0, 1);
        float xoff = 0.; //rng.randomFloat(-0.5, 0.5);
        float yoff = 0.; //rng.randomFloat(-0.5, 0.5);
        b.trail.push_back(new_particle(b.pos, {-b.vel.x * trail_limiter + xoff, -b.vel.y * trail_limiter + yoff}, b.clr, rng.randomInt(1, 3), 30));
    }
    trail_update(b);
}

void ball_destroy(Ball& b, GameState& g) {
    for (int i = 0; i < 60; ++i) {
        vector_2d particle_vel = {rng.randomFloat(-4.0f, 4.0f), rng.randomFloat(-4.0f, 4.0f)};
        g.particles.push_back(new_particle(b.pos, particle_vel, b.clr, rng.randomInt(1,2), 60));
    }
}

void ball_draw(Ball& b) {
    trail_draw(b);
    fill_circle(b.clr, b.pos.x, b.pos.y, b.size);
}

void trail_update(Ball& b) {
    for (auto& p : b.trail) {
        particle_update(p);
    }
    // Remove dead particles
    b.trail.erase(std::remove_if(b.trail.begin(), b.trail.end(),
                                 [](const Particle& p) { return p.ttl <= 0; }),
                  b.trail.end());
}

void trail_draw(Ball& b) {
    for (auto& p : b.trail) {
        particle_draw(p);
    }
}

void ball_check_wall_collision(Ball& b) {
    if (b.pos.y > GAME_AREA_HEIGHT) {
        b.active = false;
        return;
    }
    if (b.pos.x < GAME_AREA_START + b.size || b.pos.x > GAME_AREA_END - b.size - 1) {
        b.pos.x = (b.pos.x < GAME_AREA_START + b.size) ? GAME_AREA_START + b.size : GAME_AREA_END - b.size - 1;
        b.vel.x *= -1.;
    }
    if (b.pos.y < 0 + b.size) {
        b.pos.y = 0 + b.size;
        b.vel.y *= -1.;
    }
}

void ball_check_block_collision(Ball& b, GameState& g) {
    for (auto& row : g.terrain) {
        for (auto& block : row) {
            if (block && block->active) {
                // Check for collision
                if (b.pos.x < block->pos.x + block->width && b.pos.x + b.size > block->pos.x &&
                    b.pos.y < block->pos.y + block->height && b.pos.y + b.size > block->pos.y) {
                    block->active = false;

                    // Determine collision direction
                    float overlapLeft = (block->pos.x + block->width) - b.pos.x;
                    float overlapRight = (b.pos.x + b.size) - block->pos.x;
                    float overlapTop = (block->pos.y + block->height) - b.pos.y;
                    float overlapBottom = (b.pos.y + b.size) - block->pos.y;

                    // block effect
                    if (rng.chance(BLOCK_POWERUP_CHANCE)) {
                        Ball nb = roll_ball();
                        nb.pos = block->pos;
                        g.balls.push_back(nb);
                        for (int i = 0; i < 15; ++i) {
                            vector_2d particle_vel = {rng.randomFloat(-2.0f, 2.0f), rng.randomFloat(-2.0f, 2.0f)};
                            g.particles.push_back(new_particle(block->pos, particle_vel, nb.clr, 2, 60));
                        }
                    }

                    if (b.ttl_type == 1) --b.ttl;
                    // Call the block effect, effect function should return false if the ball trajectory won't change
                    // as is the case with acid for example
                    bool should_vel = b.effect(b, block->grid_pos, g);
                    if (!should_vel) {
                        return;
                    }

                    bool x_overlap = std::min(overlapLeft, overlapRight) < std::min(overlapTop, overlapBottom);
                    // Reverse velocity based on the smallest overlap
                    if (x_overlap) {
                        b.vel.x *= -1; // Horizontal collision
                    } else {
                        b.vel.y *= -1; // Vertical collision
                    }
                }
            }
        }
    }
}

void ball_check_paddle_collision(Ball& b, GameState& g) {
    if (b.pos.x < g.paddle.x + g.paddle.width && b.pos.x + b.size > g.paddle.x && b.pos.y >= g.paddle.y) {
        b.vel.y *= -1;
        b.vel.x = map_value(b.pos.x - (g.paddle.x + g.paddle.width / 2), 0, g.paddle.width / 2, 0, 5);
    }
}


void update_balls(GameState& g) {
    for (auto& b : g.balls) {
        ball_update(b, g);
        if (!b.active) {
            ball_destroy(b, g);
        }
    }
    g.balls.erase(remove_if(g.balls.begin(), g.balls.end(), [](const Ball& b) { return !b.active; }), g.balls.end());
}

void draw_balls(GameState& g) {
    for (auto& b : g.balls) {
        ball_draw(b);
    }
}
