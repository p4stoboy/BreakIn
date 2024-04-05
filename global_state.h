#pragma once

#include "types.h"
#include "particle_state.h"
#include "terrain_state.h"
#include "paddle_state.h"
#include "bullet_state.h"

void update_global_state(GameState& g) {
    update_particles(g);
    update_terrain(g);
    paddle_update(g);
    update_bullets(g);
    draw_particles(g);
    draw_terrain(g);
    paddle_draw(g);
    draw_bullets(g);
}
