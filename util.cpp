#include "splashkit.h"
#include "stdio.h"

color color_from_hex(const std::string& hex) {
    int r, g, b;
    sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
    return rgb_color(r, g, b);
}

double map_value(double value, double input_min, double input_max, double output_min, double output_max) {
    // Calculate the ratio between the input range and output range
    double scale = (output_max - output_min) / (input_max - input_min);
    // Map the value to the new range
    return output_min + (value - input_min) * scale;
}
