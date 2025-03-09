#include "RovePainter.h"

void RovePainter::drawImage(Image image, int32_t xPos, int32_t yPos) {
    if (!m_canvas) return;
    if (!image.dataPtr) return;

    const uint8_t *pixel = image.dataPtr;
    for (int32_t y = yPos; y < yPos + image.height; y++) {
        for (int32_t x = xPos; x < xPos + image.width; x++) {
            m_canvas->setPixelRGB(x, y, {pixel[0], pixel[1], pixel[2]});
            pixel += 3;
        }
    }
}
