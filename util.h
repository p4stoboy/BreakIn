#pragma once

#include "splashkit.h"
#include "stdio.h"
#include <stdexcept>

color color_from_hex(const std::string& hex);

template<typename T>
T clamp(const T& value, const T& low, const T& high);

template<typename T>
T choose(const std::vector<T>& vec);

template<typename T, size_t N>
T choose(const T (&arr)[N]);

double map_value(double value, double input_min, double input_max, double output_min, double output_max);


template<typename T>
T choose(const std::vector<T>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Vector is empty");
    }
    // Assuming rng is a function that generates a random index
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
