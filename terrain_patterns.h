#pragma once

#include "types.h"

/**
 * @brief Generate a grid pattern with the given number of rows and columns.
 *
 * @param rows The number of rows in the grid.
 * @param cols The number of columns in the grid.
 * @return Grid The generated grid.
 */
Grid grid_pattern(int rows, int cols);
Grid sine_pattern(int rows, int cols);
Grid circle_lattice_pattern(int rows, int cols);
Grid sine_landscape(int rows, int cols);

/**
 * @brief Check if a position is on the edge of a rectangle.
 *
 * @param pos The position to check.
 * @param start The start position of the rectangle.
 * @param end The end position of the rectangle.
 * @param thresh The threshold for the edge.
 * @return true If the position is on the edge.
 * @return false If the position is not on the edge.
 */
bool is_edge(ivec2 pos, ivec2 start, ivec2 end, int thresh);
