#include "RovePanelMap.h"

RovePanelMap::RovePanelMap() {
    // nothing to do yet
}

void RovePanelMap::begin() {
    PanelDescriptor *begin = m_panels, *end = m_panels + m_panelCount;
    for (PanelDescriptor *it = begin; it < end; ++it) {
        if (it->panel) {
            it->panel->begin();
        }
    }
}

void RovePanelMap::addPanel(int32_t x, int32_t y, RoveLightingPanel *panel) {
    if (m_panelCount < MAX_LIGHTING_PANELS) {
        PanelDescriptor &desc = m_panels[m_panelCount++];
        desc.x = x;
        desc.y = y;
        desc.panel = panel;
        desc.modified = true;
    }
}

void RovePanelMap::show() {
    PanelDescriptor *begin = m_panels, *end = m_panels + m_panelCount;
    for (PanelDescriptor *it = begin; it < end; ++it) {
        if (it->modified) {
            it->panel->show();
        }
    }
}

void RovePanelMap::fill(Color color) {
    PanelDescriptor *begin = m_panels, *end = m_panels + m_panelCount;
    for (PanelDescriptor *it = begin; it < end; ++it) {
        if (it->panel) {
            it->panel->fill(color);
        }
    }
}

void RovePanelMap::clear() {
    PanelDescriptor *begin = m_panels, *end = m_panels + m_panelCount;
    for (PanelDescriptor *it = begin; it < end; ++it) {
        if (it->panel) {
            it->panel->clear();
        }
    }
}

void RovePanelMap::setPixelRGB(int32_t x, int32_t y, Color color) {
    PanelDescriptor *begin = m_panels, *end = m_panels + m_panelCount;
    for (PanelDescriptor *it = begin; it < end; ++it) {
        if (isInBounds(x, y, *it)) {
            int32_t panelX = x - it->x;
            int32_t panelY = y - it->y;
            it->panel->setPixelRGB(panelX, panelY, color);
        }
    }
}

void RovePanelMap::setPixelGrayscale(int32_t x, int32_t y, uint8_t value) {
    PanelDescriptor *begin = m_panels, *end = m_panels + m_panelCount;
    for (PanelDescriptor *it = begin; it < end; ++it) {
        if (isInBounds(x, y, *it)) {
            int32_t panelX = x - it->x;
            int32_t panelY = y - it->y;
            it->panel->setPixelGrayscale(panelX, panelY, value);
        }
    }
}

bool RovePanelMap::isInBounds(int32_t x, int32_t y, const PanelDescriptor &panelDesc) {
    return (x >= panelDesc.x && x < panelDesc.x + panelDesc.panel->getWidth()) &&
           (y >= panelDesc.y && y < panelDesc.y + panelDesc.panel->getHeight());
}
