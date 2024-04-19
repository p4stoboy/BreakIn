#include "splashkit.h"
#include "XOR.h"
#include "globals.h"
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
            bool edge =is_edge({x, y}, {x_start, 0}, {x_end, rows}, 2);
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
            bool edge =is_edge({x, y}, {x_start, 0}, {x_end, rows}, 2);
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


// Function to generate a grid pattern with circles
Grid circle_lattice_pattern(int rows, int cols) {
    Grid chunk;
    int x_start = (NUM_COLS - cols) / 2;
    int x_end = x_start + cols;

    int num_circs = rng.randomInt(20, 40);

    std::vector<std::tuple<int, int, int>> centroids;  // x, y, radius
    int i = 0;
    while (i < num_circs) {
        int cy = rng.randomInt(0, rows);
        int cx = rng.randomInt(x_start, x_end);
        // radius is distance to closest edge or existing circle
        int min_dist = 800;
        for (const auto& [centroid_x, centroid_y, r] : centroids) {
            int dx = cx - centroid_x;
            int dy = cy - centroid_y;
            int dist = std::sqrt(dx * dx + dy * dy) - r;
            min_dist = dist < min_dist ? dist : min_dist;
        }
        int min_edge = std::min(std::min(cx - x_start, x_end - cx), std::min(cy, rows - cy));
        min_dist = min_dist < min_edge ? min_dist : min_edge;
        int radius = min_dist * 1.3;
        centroids.push_back({cx, cy, radius});
        ++i;
    }

    for (int y = 0; y < rows; ++y) {
        Row new_row;
        for (int x = 0; x < NUM_COLS; ++x) {
            bool in_circle = false;
            for (const auto& [centroid_x, centroid_y, radius] : centroids) {
                double dx = x - centroid_x;
                double dy = y - centroid_y;
                float dist = std::min(dx, dy);
                if (dist <= radius && dist >= radius / 1.2f) {
                    in_circle = true;
                    break;
                }
            }
            bool edge =is_edge({x, y}, {x_start, 0}, {x_end, rows}, 2);
            bool in = x >= x_start && x < x_end;
            if ((in_circle || edge) && in) {
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


Grid sine_landscape(int rows, int cols) {
    bool x_ax = rng.chance(0.5);
    float scale = rng.randomFloat(0.01, 0.1);
    Grid chunk;
    int x_start = (NUM_COLS - cols) / 2;
    int x_end = x_start + cols;
    for (int y = 0; y < rows; ++y) {
        Row new_row;
        for (int x = 0; x < NUM_COLS; ++x) {
            bool edge =is_edge({x, y}, {x_start, 0}, {x_end, rows}, 2);
            bool in = x >= x_start && x < x_end;
            bool sine = std::sin(static_cast<float>(x) * scale) * rows <= y;
            if ((sine || edge) && in) {
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


bool is_edge(ivec2 pos, ivec2 start, ivec2 end, int thresh) {
    return pos.x < start.x + thresh || pos.x >= end.x - thresh || pos.y < start.y + thresh || pos.y >= end.y - thresh;
}

