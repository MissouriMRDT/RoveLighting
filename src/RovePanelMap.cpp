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

void RovePanelMap::addPanel(RoveLightingPanel *panel, int32_t x, int32_t y) {
    if (m_panelCount >= MAX_LIGHTING_PANELS) return;
    PanelDescriptor &desc = m_panels[m_panelCount++];
    desc.panel = panel;
    desc.x = x;
    desc.y = y;
    desc.modified = true;

    if (x < m_left) m_left = x;
    if (y < m_top) m_top = y;
    if (x + panel->getWidth() > m_right) m_right = x + panel->getWidth();
    if (y + panel->getHeight() > m_bottom) m_bottom = y + panel->getHeight();
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

void RovePanelMap::setPixelColor(int32_t x, int32_t y, Color color) {
    PanelDescriptor *begin = m_panels, *end = m_panels + m_panelCount;
    for (PanelDescriptor *it = begin; it < end; ++it) {
        if (isInBounds(x, y, *it)) {
            int32_t panelX = x - it->x;
            int32_t panelY = y - it->y;
            it->panel->setPixelColor(panelX, panelY, color);
        }
    }
}

void RovePanelMap::setPixelRGB(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b) {
    PanelDescriptor *begin = m_panels, *end = m_panels + m_panelCount;
    for (PanelDescriptor *it = begin; it < end; ++it) {
        if (isInBounds(x, y, *it)) {
            int32_t panelX = x - it->x;
            int32_t panelY = y - it->y;
            it->panel->setPixelRGB(panelX, panelY, r, g, b);
        }
    }
}

void RovePanelMap::setPixelRGBA(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    PanelDescriptor *begin = m_panels, *end = m_panels + m_panelCount;
    for (PanelDescriptor *it = begin; it < end; ++it) {
        if (isInBounds(x, y, *it)) {
            int32_t panelX = x - it->x;
            int32_t panelY = y - it->y;
            it->panel->setPixelRGBA(panelX, panelY, r, g, b, a);
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
