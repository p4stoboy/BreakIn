#include "types.h"
#include "splashkit.h"
#include "values.h"
#include "init_state.h"
#include "bullet_state.h"
#include "global_state.h"

int main()
{
    open_window("upDig", WINDOW_WIDTH, WINDOW_HEIGHT);
    GameState game = new_game_state();
    game.terrain = grid_pattern(NUM_ROWS, NUM_COLS);
    hide_mouse();
    while (!quit_requested())
    {
        process_events();
        clear_screen(COLOR_BLACK);
        fill_rectangle(clr_background, SCREEN_START, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        if (game.status == PLAYING) {

            // DEBUG
            if (mouse_clicked(MOUSE_X1_BUTTON)) {
                game.bullets.push_back(new_bullet({static_cast<double>(rng.randomInt(SCREEN_START, SCREEN_END)), static_cast<double>(SCREEN_HEIGHT-100)}, {3, -3}, 3, clr_bullet_standard, bullet_standard));
            } else if (mouse_clicked(MOUSE_X2_BUTTON)) {
                game.bullets.push_back(new_bullet({static_cast<double>(rng.randomInt(SCREEN_START, SCREEN_END)), static_cast<double>(SCREEN_HEIGHT-100)}, {3, -3}, 3, clr_bullet_acid, bullet_explosion));
            }
            // END DEBUG

            update_global_state(game);
        }
        refresh_screen(60);
    }
    return 0;
}
