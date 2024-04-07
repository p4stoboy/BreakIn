#include "splashkit.h"
#include "XOR.h"
#include "values.h"
#include "terrain_patterns.h"
#include <cmath>
#include "state_init.h"


Grid grid_pattern(int rows, int cols) {
    Grid chunk;
    int mod_x = rng.randomInt(2, 20);
    int mod_y = rng.randomInt(2, 20);
    int mod_thresh = rng.randomInt(1, std::min(mod_x, mod_y));
    int x_start = (NUM_COLS - cols) / 2;
    int x_end = x_start + cols;
    for (int y = 0; y < rows; ++y) {
        Row new_row;
        for (int x = 0; x < NUM_COLS; ++x) {
            bool edge = y == 0 || y == rows - 1 || x == x_start || x == x_end - 1;
            bool in = x >= x_start && x < x_end;
            if ((x % mod_x < mod_thresh || y % mod_y < mod_thresh || edge) && in) {
                point_2d pos = {static_cast<double>(TERRAIN_OFFSET + x * BLOCK_WIDTH), 0.0f};
                point_2d target_pos = {pos.x, static_cast<double>(y * BLOCK_HEIGHT)};
                ivec2 grid_pos = {x, y};
                new_row.push_back(std::make_unique<Block>(new_block(pos, target_pos, grid_pos, BLOCK_WIDTH, BLOCK_HEIGHT, clr_block)));
            } else {
                new_row.push_back(nullptr);
            }
        }
        chunk.push_back(std::move(new_row));
    }
    return chunk;
}


Grid sine_pattern(int rows, int cols) {
    bool x_ax = rng.chance(0.5);
    float scale = rng.randomFloat(0.1, 1.0);
    Grid chunk;
    int x_start = (NUM_COLS - cols) / 2;
    int x_end = x_start + cols;
    for (int y = 0; y < rows; ++y) {
        Row new_row;
        for (int x = 0; x < NUM_COLS; ++x) {
            bool edge = y == 0 || y == rows - 1 || x == x_start || x == x_end - 1;
            bool in = x >= x_start && x < x_end;
            if (((x_ax ? std::sin(static_cast<float>(x) * scale) : std::sin(static_cast<float>(y) * scale)) > 0.5f || edge) && in) {
                point_2d pos = {static_cast<double>(TERRAIN_OFFSET + x * BLOCK_WIDTH), 0.0};
                point_2d target_pos = {pos.x, static_cast<double>(y * BLOCK_HEIGHT)};
                ivec2 grid_pos = {x, y};
                new_row.push_back(std::make_unique<Block>(new_block(pos, target_pos, grid_pos, BLOCK_WIDTH, BLOCK_HEIGHT, clr_block)));
            } else {
                new_row.push_back(nullptr);
            }
        }
        chunk.push_back(std::move(new_row));
    }
    return chunk;
}
