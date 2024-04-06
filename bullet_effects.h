#pragma once

#include "types.h"

bool bullet_standard(Bullet& b, ivec2 grid_pos, GameState& game) {
    for (int i = 0; i < 3; ++i) {
        game.particles.push_back(new_particle(b.pos, {rng.randomFloat(-2, 2), rng.randomFloat(-2, 2)}, b.clr, 2, 30));
    }
    return true;
}

bool bullet_explosion(Bullet& b, ivec2 grid_pos, GameState& game) {
    // deactivate blocks in radius of explosion
    for (int _y= -4; _y<= 4; ++_y) {
        for (int _x= -4; _x<= 4; ++_x) {
            if (grid_pos.x + _y >= 0 && grid_pos.x + _y < game.terrain[0].size() && grid_pos.y + _x >= 0 && grid_pos.y + _x < game.terrain.size()) {
                if (game.terrain[grid_pos.y + _x][grid_pos.x + _y]) {
                    game.terrain[grid_pos.y + _x][grid_pos.x + _y]->active = false;
                }
            }
        }
    }
    for (int i = 0; i < 30; ++i) {
        game.particles.push_back(new_particle(b.pos, {rng.randomFloat(-2, 2), rng.randomFloat(-2, 2)}, b.clr, 2, 30));
    }
    return true;
}

bool bullet_acid(Bullet& b, ivec2 grid_pos, GameState& game) {
    return false;
}
