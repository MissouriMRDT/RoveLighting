#ifndef ROVECANVAS_H
#define ROVECANVAS_H

#include <stdint.h>

#include "RoveLightingUtils.h"

class RoveCanvas {
public:
    virtual void show() = 0;
    virtual void fill(Color color) = 0;
    virtual void clear() = 0;
    virtual void setPixelColor(int32_t x, int32_t y, Color color) = 0;
    virtual void setPixelRGB(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void setPixelRGBA(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void setPixelGrayscale(int32_t x, int32_t y, uint8_t value) = 0;
};

#endif // ROVECANVAS_H