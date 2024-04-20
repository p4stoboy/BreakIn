#include "include/XOR.h"

XOR::XOR(uint32_t initialSeed) : seed(initialSeed) {}

uint32_t XOR::next() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

int XOR::randomInt(int min, int max) {
    if (max < min) {
        std::swap(min, max);
    }
    uint32_t range = static_cast<uint32_t>(max - min + 1);
    return min + static_cast<int>(next() % range);
}

float XOR::randomFloat(float min, float max) {
    // Normalize to [0, 1)
    float normalized = next() * (1.0f / 4294967296.0f); // 2^32
    // Scale and shift to [min, max)
    return min + normalized * (max - min);
}

bool XOR::chance(float probability) {
    return randomFloat() < probability;
}
