#pragma once

#include "types.h"

Grid grid_pattern(int rows, int cols);
Grid sine_pattern(int rows, int cols);
Grid circle_lattice_pattern(int rows, int cols);
Grid sine_landscape(int rows, int cols);

bool is_edge(ivec2 pos, ivec2 start, ivec2 end, int thresh);
