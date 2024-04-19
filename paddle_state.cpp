#include "globals.h"
#include "state_management.h"
#include "splashkit.h"
#include "util.h"

void paddle_update(GameState& g) {
    g.paddle.x = clamp((int) mouse_x(), GAME_AREA_START, GAME_AREA_END - g.paddle.width);
}

void paddle_draw(GameState& g) {
    fill_rectangle(g.paddle.clr, g.paddle.x, g.paddle.y, g.paddle.width, g.paddle.height);
}
