#ifndef ROVELIGHTINGUTILS_H
#define ROVELIGHTINGUTILS_H

#include <stdint.h>

struct Color {
    uint8_t r, g, b;
    bool transparent;
};

const Color WHITE = {255, 255, 255};
const Color RED = {255, 0, 0};
const Color YELLOW = {255, 255, 0};
const Color GREEN = {0, 255, 0};
const Color CYAN = {0, 255, 255};
const Color BLUE = {0, 0, 255};
const Color MAGENTA = {255, 0, 255};
const Color CLEAR = {0, 0, 0, true};

#endif // ROVELIGHTINGUTILS_H
