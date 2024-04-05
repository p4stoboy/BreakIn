#pragma once

#include "types.h"
#include "splashkit.h"
#include "values.h"

void paddle_update(GameState& g);
void paddle_draw(GameState& g);

void paddle_update(GameState& g) {
    g.paddle.x = clamp((int) mouse_x(), SCREEN_START, SCREEN_END - g.paddle.width);
}

void paddle_draw(GameState& g) {
    fill_rectangle(g.paddle.clr, g.paddle.x, g.paddle.y, g.paddle.width, 10);
}


