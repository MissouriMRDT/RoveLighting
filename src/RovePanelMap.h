#ifndef ROVEPANELMAP_H
#define ROVEPANELMAP_H

#include "RoveLightingPanel.h"

#define MAX_LIGHTING_PANELS 16

class RovePanelMap : public RoveCanvas {
private:

struct PanelDescriptor {
    int32_t x, y;
    RoveLightingPanel *panel;
};

uint8_t m_panelCount = 0;
PanelDescriptor m_panels[MAX_LIGHTING_PANELS] = {0};

public:
    RovePanelMap();

    void fill(Color color) override;
    void clear() override;
    void setPixelRGB(int32_t x, int32_t y, Color color) override;
    void setPixelGrayscale(int32_t x, int32_t y, uint8_t value) override;

private:
    static bool isInBounds(int32_t x, int32_t y, const PanelDescriptor &panel);

};

#endif // ROVEPANELMAP_H
