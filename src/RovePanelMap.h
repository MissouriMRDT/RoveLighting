#ifndef ROVEPANELMAP_H
#define ROVEPANELMAP_H

#include "RoveLightingPanel.h"

#define MAX_LIGHTING_PANELS 16

class RovePanelMap : public RoveCanvas {
private:
    struct PanelDescriptor {
        RoveLightingPanel *panel;
        int32_t x, y;
        bool modified;
    };

    uint8_t m_panelCount = 0;
    PanelDescriptor m_panels[MAX_LIGHTING_PANELS] = {0};

    int32_t m_top = 0;
    int32_t m_left = 0;
    int32_t m_right = 0;
    int32_t m_bottom = 0;

public:
    RovePanelMap();
    void begin();
    void addPanel(RoveLightingPanel *panel, int32_t x, int32_t y);

    void show() override;
    void fill(Color color) override;
    void clear() override;
    void setPixelRGB(int32_t x, int32_t y, Color color) override;
    void setPixelGrayscale(int32_t x, int32_t y, uint8_t value) override;

    uint32_t getWidth() const { return m_right - m_left; }
    uint32_t getHeight() const { return m_bottom - m_top; }

private:
    static bool isInBounds(int32_t x, int32_t y, const PanelDescriptor &panel);

};

#endif // ROVEPANELMAP_H
