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
const Color TRANSPARENT = {0, 0, 0, true};

enum class FrameType {
    COLOR, IMAGE,
};

enum class ColorFormat {
    GRAYSCALE,     // 8 bits per pixel
    RGB,           // 24 bits per pixel
    RGBA,          // 32 bits per pixel
    BITMAP,        // 1 byte per pixel, treated as bool
    BITMAP_PACKED, // 8 bits for 8 pixels
};

struct Image {
    uint32_t width, height;
    ColorFormat colorFormat;
    const uint8_t *dataPtr;
};

struct Font {
    uint8_t letterWidth, letterHeight;
    char firstChar, lastChar;
    const uint8_t **letterData;
    const uint8_t *letterWidths;
};

struct FontSet {
    Font *fontRegular;
    Font *fontBold;
    Font *fontItalic;
};


#endif // ROVELIGHTINGUTILS_H
