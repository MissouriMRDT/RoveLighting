#ifndef ROVEPAINTER_H
#define ROVEPAINTER_H

#include "RoveLightingUtils.h"
#include "RoveCanvas.h"

class RovePainter {
private:
    RoveCanvas *m_canvas = nullptr;

public:
    RovePainter() {}
    RovePainter(RoveCanvas *canvas) : m_canvas(canvas) {}

    void drawImage(Image image, int32_t x, int32_t y);

    void setCanvas(RoveCanvas *canvas) { m_canvas = canvas; }
};

#endif // ROVEPAINTER_H
