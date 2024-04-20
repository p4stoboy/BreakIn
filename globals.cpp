#include "include/globals.h"
#include "splashkit.h"
#include "include/XOR.h"
#include "include/util.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int GAME_AREA_WIDTH = 600;
const int GAME_AREA_HEIGHT = 1000;
const int GAME_AREA_OFFSET = (WINDOW_WIDTH-GAME_AREA_WIDTH) / 2;
const int GAME_AREA_START = GAME_AREA_OFFSET;
const int GAME_AREA_END = GAME_AREA_START + GAME_AREA_WIDTH;
const int TERRAIN_OFFSET = GAME_AREA_OFFSET + GAME_AREA_WIDTH / 10;
const int TERRAIN_WIDTH = GAME_AREA_WIDTH - GAME_AREA_WIDTH / 5;
const int TERRAIN_HEIGHT = TERRAIN_WIDTH;
const int NUM_ROWS = 73;
const int NUM_COLS = 73;
const int BLOCK_WIDTH = TERRAIN_WIDTH / NUM_COLS;
const int BLOCK_HEIGHT = TERRAIN_HEIGHT / NUM_ROWS;
const float BLOCK_POWERUP_CHANCE = 0.02;
const int INITIAL_PADDLE_WIDTH = WINDOW_WIDTH / 10;

// screen shake
int SSX = 0;
int SSY = 0;

// rng
XOR rng = XOR();

//color clr_background = color_from_hex("#FBF6E0");
//color clr_paddle = color_from_hex("#E0311C");
//color clr_block = color_from_hex("#E0311C");
//color clr_ball_standard = color_from_hex("#267295");
//color clr_ball_explosion = color_from_hex("#F8BF1F");
//color clr_ball_acid = color_from_hex("#56B187");

const color clr_background = color_from_hex("#000000");
const color clr_paddle = color_from_hex("#FBF6E0");
const color clr_block = color_from_hex("#FBF6E0");
const color clr_ball_standard = color_from_hex("#FBF6E0");
const color clr_ball_explosion = color_from_hex("#FF2727");
const color clr_ball_acid = color_from_hex("#AFFF26");
