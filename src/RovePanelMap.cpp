#include "RovePanelMap.h"

RovePanelMap::RovePanelMap() {
    for (int i = 0; i < MAX_LIGHTING_PANELS; i++) {
        m_panels[i].panel = nullptr;
    }
}

void RovePanelMap::fill(Color color) {
    for (PanelDescriptor &desc : m_panels) {
        if (desc.panel) {
            desc.panel->fill(color);
        }
    }
}

void RovePanelMap::clear() {
    for (PanelDescriptor &desc : m_panels) {
        if (desc.panel) {
            desc.panel->clear();
        }
    }
}

void RovePanelMap::setPixelRGB(int32_t x, int32_t y, Color color) {
    for (PanelDescriptor &desc : m_panels) {
        if (isInBounds(x, y, desc)) {
            int32_t panelX = x - desc.x;
            int32_t panelY = y - desc.y;
            desc.panel->setPixelRGB(panelX, panelY, color);
        }
    }
}

void RovePanelMap::setPixelGrayscale(int32_t x, int32_t y, uint8_t value) {
    for (PanelDescriptor &desc : m_panels) {
        if (isInBounds(x, y, desc)) {
            int32_t panelX = x - desc.x;
            int32_t panelY = y - desc.y;
            desc.panel->setPixelGrayscale(panelX, panelY, value);
        }
    }
}

bool RovePanelMap::isInBounds(int32_t x, int32_t y, const PanelDescriptor &panelDesc) {
    return (x >= panelDesc.x && x < panelDesc.x + panelDesc.panel->getWidth()) &&
           (y >= panelDesc.y && y < panelDesc.y + panelDesc.panel->getHeight());
}
