#include "values.h"
#include "state_management.h"
#include "splashkit.h"
#include "util.h"

void paddle_update(GameState& g) {
    g.paddle.x = clamp((int) mouse_x(), SCREEN_START, SCREEN_END - g.paddle.width);
}

void paddle_draw(GameState& g) {
    fill_rectangle(g.paddle.clr, g.paddle.x, g.paddle.y, g.paddle.width, 10);
}
