#pragma once

#include <cstdint>
#include <algorithm> // For std::swap

struct XOR {
    XOR(uint32_t initialSeed = 0x77777777);
    int randomInt(int min, int max);
    float randomFloat(float min = 0.0f, float max = 1.0f);
    bool chance(float probability = 0.5f);

private:
    uint32_t next();
    uint32_t seed;
};

