#include "include/state_management.h"
#include "include/terrain_patterns.h"
#include "include/globals.h"
#include <stack>
#include "include/util.h"


int count_non_empty_rows(GameState& g) {
    int non_empty_rows = 0;
    for (const auto& row : g.terrain) {
        if (std::any_of(row.begin(), row.end(), [](const std::unique_ptr<Block>& block) { return block != nullptr; })) {
            ++non_empty_rows;
        }
    }
    return non_empty_rows;
}

void shift_rows_down(GameState& g, int num_rows_to_shift) {
    if (num_rows_to_shift <= 0) return;

    // Shift rows down
    for (int y = g.terrain.size() - 1; y >= num_rows_to_shift; --y) {
        g.terrain[y] = std::move(g.terrain[y - num_rows_to_shift]);
        for (auto &block : g.terrain[y]) {
            if (block) {
                block->target_pos.y += BLOCK_HEIGHT * num_rows_to_shift;
                block->grid_pos.y += num_rows_to_shift;
            }
        }
    }
    // Clear the top rows
    for (int y = 0; y < num_rows_to_shift; ++y) {
        for (auto &block : g.terrain[y]) {
            block.reset(); // Set each element to nullptr
        }
    }
}


void add_new_chunk(GameState& g, int num_rows, std::function<Grid(int, int)> pattern_func) {
    int num_cols = rng.randomInt(20, NUM_COLS);
    Grid new_chunk = pattern_func(num_rows, num_cols);

    // Add the new chunk at the top
    for (int y = 0; y < num_rows; ++y) {
        g.terrain[y] = std::move(new_chunk[y]);
        for (auto &block : g.terrain[y]) {
            if (block) {
                block->target_pos.y = y * BLOCK_HEIGHT;
            }
        }
    }
}


void update_terrain(GameState& g) {

    // Check if the bottom row is completely empty
    bool bottom_row_empty = true;
    for (auto& block : g.terrain.back()) {
        if (block) {
            bottom_row_empty = false;
            break;
        }
    }

    // Shift rows down and add a new chunk at the top if the bottom row is empty
    if (bottom_row_empty) {
        int non_empty_rows = count_non_empty_rows(g);
        int num_rows_to_shift = NUM_ROWS - non_empty_rows;

        if (num_rows_to_shift > 0) {
            PatternFunc pattern_func = choose({sine_landscape, grid_pattern, sine_pattern, circle_lattice_pattern}); //
            shift_rows_down(g, num_rows_to_shift);
            add_new_chunk(g, num_rows_to_shift, pattern_func);
        }
    }

    // Deactivate disconnected clusters
    deactivate_disconnected_clusters(g);

    // Update each block
    for (auto& row : g.terrain) {
        for (auto& block : row) {
            if (block) {
                block_update(*block, g);
            }
        }
    }

    // Remove destroyed blocks
    for (auto& row : g.terrain) {
        for (auto& block : row) {
            if (block && !block->active) {
                block.reset(); // Automatically deletes the block and sets the pointer to nullptr
            }
        }
    }
}


void draw_terrain(GameState& g) {
    for (const auto& row : g.terrain) {
        for (const auto& block : row) {
            if (block) {
                block_draw(*block);
            }
        }
    }
}


void dfs_mark_reachable(GameState& g, int row, int col, std::vector<std::vector<bool>>& visited) {
    std::stack<std::pair<int, int>> stack;
    stack.push({row, col});

    while (!stack.empty()) {
        auto pair = stack.top();
        int r = pair.first;
        int c = pair.second;
        stack.pop();

        if (r < 0 || r >= g.terrain.size() || c < 0 || c >= g.terrain[r].size() || !g.terrain[r][c] || visited[r][c]) {
            continue;
        }

        visited[r][c] = true;

        // Check adjacent blocks
        stack.push({r - 1, c}); // above
        stack.push({r + 1, c}); // below
        stack.push({r, c - 1}); // left
        stack.push({r, c + 1}); // right
    }
}

/**
 * @brief Uses DFS to check if blocks are not connected to top row (have been shaved off main body of terrain)
 * and deactivates them.
 * @visited array is used to mark blocks that are reachable from the top row (is a boolean map of terrain grid).
 * @param g The game state.
 */
void deactivate_disconnected_clusters(GameState& g) {
    std::vector<std::vector<bool>> visited(NUM_ROWS, std::vector<bool>(NUM_COLS, false));

    // Mark all reachable blocks starting from the top row
    for (int col = 0; col < NUM_COLS; ++col) {
        if (g.terrain[0][col]) {
            dfs_mark_reachable(g, 0, col, visited);
        }
    }

    // Deactivate all unvisited (disconnected) blocks
    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            if (g.terrain[row][col] && !visited[row][col]) {
                g.terrain[row][col]->active = false;
            }
        }
    }
}
