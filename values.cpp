#include "values.h"
#include "splashkit.h"
#include "XOR.h"
#include "util.h"

int WINDOW_WIDTH = 1000;
int WINDOW_HEIGHT = 1000;
int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 1000;
int WINDOW_OFFSET = (WINDOW_WIDTH-SCREEN_WIDTH) / 2;
int TERRAIN_OFFSET = WINDOW_OFFSET + SCREEN_WIDTH / 10;
int TERRAIN_WIDTH = SCREEN_WIDTH - SCREEN_WIDTH / 5;
int TERRAIN_HEIGHT = TERRAIN_WIDTH;
int SCREEN_START = WINDOW_OFFSET;
int SCREEN_END = SCREEN_START + SCREEN_WIDTH;
int NUM_ROWS = 60;
int NUM_COLS = 60;
int BLOCK_WIDTH = TERRAIN_WIDTH / NUM_COLS;
int BLOCK_HEIGHT = TERRAIN_HEIGHT / NUM_ROWS;
float BLOCK_POWERUP_CHANCE = 0.02;

// screen shake
int SSX = 0;
int SSY = 0;

// rng
XOR rng = XOR();

color clr_background = color_from_hex("#FBF6E0");
color clr_paddle = color_from_hex("#E0311C");
color clr_block = color_from_hex("#E0311C");
color clr_bullet_standard = color_from_hex("#267295");
color clr_bullet_explosion = color_from_hex("#F8BF1F");
color clr_bullet_acid = color_from_hex("#56B187");
