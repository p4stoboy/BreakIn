#pragma once

#include "types.h"
#include "splashkit.h"
#include <vector>
#include <algorithm>
#include "values.h"
#include "bullet_effects.h"
#include "particle_state.h"


void bullet_update(Bullet& b, GameState& g);
void bullet_destroy(Bullet& b, GameState& g);
void bullet_draw(Bullet& b);
void bullet_check_wall_collision(Bullet& b);
void bullet_check_block_collision(Bullet& b, GameState& g);
void bullet_check_paddle_collision(Bullet& b, GameState& g);
void trail_update(Bullet& b);
void trail_draw(Bullet& b);

// batch functions
void update_bullets(GameState& g);
void draw_bullets(GameState& g);

// bullet type functions
bool bullet_standard(Bullet& b, ivec2 grid_pos, GameState& g);
bool bullet_explosion(Bullet& b, ivec2 grid_pos, GameState& g);

// util
Bullet roll_bullet();


// implementation
void bullet_update(Bullet& b, GameState& g) {

    if (b.pos.y > SCREEN_HEIGHT) {
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
    bullet_check_wall_collision(b);
    bullet_check_block_collision(b, g);
    bullet_check_paddle_collision(b, g);
    if (rng.chance(0.25)) {
        float trail_limiter = rng.randomFloat(0, 1);
        float xoff = 0.; //rng.randomFloat(-0.5, 0.5);
        float yoff = 0.; //rng.randomFloat(-0.5, 0.5);
        b.trail.push_back(new_particle(b.pos, {-b.vel.x * trail_limiter + xoff, -b.vel.y * trail_limiter + yoff}, b.clr, rng.randomInt(1, 3), 30));
    }
    trail_update(b);
}

void bullet_destroy(Bullet& b, GameState& g) {
    for (int i = 0; i < 30; ++i) {
        vector_2d particle_vel = {rng.randomFloat(-4.0f, 4.0f), rng.randomFloat(-4.0f, 4.0f)};
        g.particles.push_back(new_particle(b.pos, particle_vel, b.clr, rng.randomInt(1,2), 60));
    }
}

void bullet_draw(Bullet& b) {
    trail_draw(b);
    fill_circle(b.clr, b.pos.x, b.pos.y, b.size);
}

void trail_update(Bullet& b) {
    for (auto& p : b.trail) {
        particle_update(p);
    }
    // Remove dead particles
    b.trail.erase(std::remove_if(b.trail.begin(), b.trail.end(),
                                 [](const Particle& p) { return p.ttl <= 0; }),
                  b.trail.end());
}

void trail_draw(Bullet& b) {
    for (auto& p : b.trail) {
        particle_draw(p);
    }
}

void bullet_check_wall_collision(Bullet& b) {
    if (b.pos.y > SCREEN_HEIGHT) {
        b.active = false;
        return;
    }
    if (b.pos.x < SCREEN_START + b.size || b.pos.x > SCREEN_END - b.size - 1) {
        b.pos.x = (b.pos.x < SCREEN_START + b.size) ? SCREEN_START + b.size : SCREEN_END - b.size - 1;
        b.vel.x *= -1.;
    }
    if (b.pos.y < 0 + b.size) {
        b.pos.y = 0 + b.size;
        b.vel.y *= -1.;
    }
}

void bullet_check_block_collision(Bullet& b, GameState& g) {
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
                        Bullet nb = roll_bullet();
                        nb.pos = block->pos;
                        g.bullets.push_back(nb);
                        for (int i = 0; i < 15; ++i) {
                            vector_2d particle_vel = {rng.randomFloat(-2.0f, 2.0f), rng.randomFloat(-2.0f, 2.0f)};
                            g.particles.push_back(new_particle(block->pos, particle_vel, nb.clr, 2, 60));
                        }
                    }

                    if (b.ttl_type == 1) --b.ttl;
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

void bullet_check_paddle_collision(Bullet& b, GameState& g) {
    if (b.pos.x < g.paddle.x + g.paddle.width && b.pos.x + b.size > g.paddle.x && b.pos.y >= g.paddle.y) {
        b.vel.y *= -1;
        b.vel.x = map_value(b.pos.x - (g.paddle.x + g.paddle.width / 2), 0, g.paddle.width / 2, 0, 5);
    }
}


void update_bullets(GameState& g) {
    for (auto& b : g.bullets) {
        bullet_update(b, g);
        if (!b.active) {
            bullet_destroy(b, g);
        }
    }
    g.bullets.erase(remove_if(g.bullets.begin(), g.bullets.end(), [](const Bullet& b) { return !b.active; }), g.bullets.end());
}

void draw_bullets(GameState& g) {
    for (auto& b : g.bullets) {
        bullet_draw(b);
    }
}

Bullet roll_bullet() {
    BulletEffect effect = bullet_standard;
    color clr = clr_bullet_standard;
    int ttl_type = 0;
    int ttl = 0;
    bool non_standard = rng.chance(0.05);
    if (non_standard) {
        bool explode = rng.chance(0.5);
        effect = explode ? bullet_explosion : bullet_acid;
        clr = explode ? clr_bullet_explosion : clr_bullet_acid;
        ttl_type = explode ? 1 : 2;
        ttl = explode ? 3 : 700;
    }
    return new_bullet({50,50}, {0, -3}, 3, clr, effect, ttl_type, ttl);
}
