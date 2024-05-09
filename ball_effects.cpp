#include "include/globals.h"
#include "splashkit.h"
#include "include/ball_effects.h"
#include "include/state_init.h"


bool ball_standard(Ball& b, ivec2 grid_pos, GameState& game) {
    for (int i = 0; i < 3; ++i) {
        game.particles.push_back(new_particle(b.pos, {rng.randomFloat(-2, 2), rng.randomFloat(-2, 2)}, b.clr, 2, 30));
    }
    return true;
}

bool ball_explosion(Ball& b, ivec2 grid_pos, GameState& game) {
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

bool ball_acid(Ball& b, ivec2 grid_pos, GameState& game) {
    return false;
}


Ball roll_ball() {
    BallEffect effect = ball_standard;
    color clr = clr_ball_standard;
    int ttl_type = 0;
    int ttl = 0;
    bool non_standard = rng.chance(0.1);
    if (non_standard) {
        bool explode = rng.chance(0.5);
        effect = explode ? ball_explosion : ball_acid;
        clr = explode ? clr_ball_explosion : clr_ball_acid;
        ttl_type = explode ? 1 : 2;
        ttl = explode ? 3 : 700;
    }
    return new_ball({50,50}, {rng.randomFloat(3, -3), -3}, 3, clr, effect, ttl_type, ttl);
}
