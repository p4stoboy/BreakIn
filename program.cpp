#include "include/globals.h"
#include "splashkit.h"
#include "include/types.h"
#include "include/state_management.h"
#include "include/state_init.h"
#include "include/terrain_patterns.h"
#include "include/ball_effects.h"
#include "include/draw.h"


int main()
{
    open_window("upDig", WINDOW_WIDTH, WINDOW_HEIGHT);
    GameState game = new_game_state();
    game.terrain = grid_pattern(NUM_ROWS, NUM_COLS);
    hide_mouse();
    while (!quit_requested())
    {
        process_events();
        if (game.status == PLAYING) {
            // draw score top left in large text
            // DEBUG
            if (mouse_clicked(MOUSE_X1_BUTTON)) {
                game.balls.push_back(new_ball({static_cast<double>(rng.randomInt(GAME_AREA_START, GAME_AREA_END)), static_cast<double>(GAME_AREA_HEIGHT-100)}, {3, -3}, 3, clr_ball_standard, ball_standard, 0, 1));
            } else if (mouse_clicked(MOUSE_X2_BUTTON)) {
                game.balls.push_back(new_ball({static_cast<double>(rng.randomInt(GAME_AREA_START, GAME_AREA_END)), static_cast<double>(GAME_AREA_HEIGHT-100)}, {3, -3}, 3, clr_ball_acid, ball_acid, 2, 700));
            }
            // END DEBUG

            update_global_state(game);
            draw_global_state(game);
        }
        refresh_screen(60);
    }
    return 0;
}
