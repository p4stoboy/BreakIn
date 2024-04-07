#include "values.h"
#include "splashkit.h"
#include "bullet_effects.h"
#include "state_init.h"


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
