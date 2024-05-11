#include "include/globals.h"
#include "include/state_management.h"
#include "include/state_init.h"
#include "include/draw.h"


void block_update(Block& b, GameState& g) {
    if (!b.active) {
        block_destroy(b, g);
        return;
    }
    if (b.pos.y < b.target_pos.y) {
        b.y_vel += 0.1;
        b.pos.y += b.y_vel;
        if (b.pos.y >= b.target_pos.y) {
            b.pos.y = b.target_pos.y;
            b.y_vel = 0;
        }
    }
}

void block_destroy(const Block& b, GameState& g) {
    ++g.score;
    for (int i = 0; i < 1; ++i) {
        vector_2d particle_vel = {rng.randomFloat(-2.0f, 2.0f), rng.randomFloat(2.0f, 0.0f)}; // can't have upward trajectory
        g.particles.push_back(new_particle(b.pos, particle_vel, b.clr, rng.randomInt(1,2), 90));
    }
}
