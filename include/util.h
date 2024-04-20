#pragma once

#include "splashkit/splashkit.h"
#include "stdio.h"
#include <stdexcept>

/**
 * @brief Convert a hex string to a color.
 *
 * @param hex The hex string.
 * @return color The color.
 */
color color_from_hex(const std::string& hex);

/**
 * @brief Clamp a value between a low and high value.
 *
 * @tparam T The value type.
 * @param value The value to clamp.
 * @param low The low value.
 * @param high The high value.
 * @return T The clamped value.
 */
template<typename T>
T clamp(const T& value, const T& low, const T& high);

/**
 * @brief Choose a random element from a vector.
 *
 * @tparam T The element type.
 * @param vec The vector.
 * @return T The chosen element.
 */
template<typename T>
T choose(const std::vector<T>& vec);

/**
 * @brief Choose a random element from an array.
 *
 * @tparam T The element type.
 * @tparam N The array size.
 * @param arr The array.
 * @return T The chosen element.
 */
template<typename T, size_t N>
T choose(const T (&arr)[N]);

/**
 * @brief Map a value from one range to another.
 *
 * @param value The value to map.
 * @param input_min The input minimum.
 * @param input_max The input maximum.
 * @param output_min The output minimum.
 * @param output_max The output maximum.
 * @return double The mapped value.
 */
double map_value(double value, double input_min, double input_max, double output_min, double output_max);


template<typename T>
T choose(const std::vector<T>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Vector is empty");
    }
    int index = std::rand() % vec.size();
    return vec[index];
}

template<typename T, size_t N>
T choose(const T (&arr)[N]) {
    return arr[std::rand() % N];
}

template<typename T>
T clamp(const T& value, const T& low, const T& high) {
    return (value < low) ? low : (value > high) ? high : value;
}
