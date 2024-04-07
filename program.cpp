#include "values.h"
#include "splashkit.h"
#include "types.h"
#include "state_management.h"
#include "state_init.h"
#include "util.h"
#include "terrain_patterns.h"
#include "bullet_effects.h"


int main()
{
    open_window("upDig", WINDOW_WIDTH, WINDOW_HEIGHT);
    GameState game = new_game_state();
    game.terrain = grid_pattern(NUM_ROWS, NUM_COLS);
    hide_mouse();
    while (!quit_requested())
    {
        process_events();
        clear_screen(color_from_hex("#F7CA8B"));
        fill_rectangle(clr_background, SCREEN_START, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        if (game.status == PLAYING) {
            // draw score top left in large text
            draw_text("score: " + std::to_string(game.score), COLOR_WHITE, 20, 20, option_to_screen());
            // DEBUG
            if (mouse_clicked(MOUSE_X1_BUTTON)) {
                game.bullets.push_back(new_bullet({static_cast<double>(rng.randomInt(SCREEN_START, SCREEN_END)), static_cast<double>(SCREEN_HEIGHT-100)}, {3, -3}, 3, clr_bullet_standard, bullet_standard, 0, 1));
            } else if (mouse_clicked(MOUSE_X2_BUTTON)) {
                game.bullets.push_back(new_bullet({static_cast<double>(rng.randomInt(SCREEN_START, SCREEN_END)), static_cast<double>(SCREEN_HEIGHT-100)}, {3, -3}, 3, clr_bullet_acid, bullet_acid, 2, 700));
            }
            // END DEBUG

            update_global_state(game);
        }
        refresh_screen(60);
    }
    return 0;
}
