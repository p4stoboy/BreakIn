#pragma once

#include "XOR.h"
#include "splashkit.h"
#include "util.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 1000;
const int WINDOW_OFFSET = (WINDOW_WIDTH - SCREEN_WIDTH) / 2;
const int TERRAIN_OFFSET = WINDOW_OFFSET + SCREEN_WIDTH / 10;
const int TERRAIN_WIDTH = SCREEN_WIDTH - SCREEN_WIDTH / 5;
const int TERRAIN_HEIGHT = TERRAIN_WIDTH;
const int SCREEN_START = WINDOW_OFFSET;
const int SCREEN_END = SCREEN_START + SCREEN_WIDTH;
const int NUM_ROWS = 60;
const int NUM_COLS = 60;
const int BLOCK_WIDTH = TERRAIN_WIDTH / NUM_COLS;
const int BLOCK_HEIGHT = TERRAIN_HEIGHT / NUM_ROWS;
const float BLOCK_POWERUP_CHANCE = 0.02;


// screen shake
int SSX = 0;
int SSY = 0;

// rng
XOR rng = XOR();


//color clr_background = color_from_hex("#252021");
//color clr_paddle = color_from_hex("#FF5227");
//color clr_block = color_from_hex("#FF9F37");
//color clr_bullet_acid = color_from_hex("#243A4B");
//color clr_bullet_explosion = color_from_hex("#4AC0AF");
//color clr_bullet_standard = color_from_hex("#FFF1C1"); //"#ACE5BA");
//color_from_hex("#FFF1C1")

color clr_background = color_from_hex("#222C3C");
color clr_paddle = color_from_hex("#E9F7FE");
color clr_block = color_from_hex("#E9F7FE");
color clr_bullet_standard = color_from_hex("#E9F7FE");
color clr_bullet_explosion = color_from_hex("#FFB64F");
color clr_bullet_acid = color_from_hex("#BEF55C");
