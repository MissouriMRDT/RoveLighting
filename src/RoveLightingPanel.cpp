#include "RoveLightingPanel.h"

RoveLightingPanel::RoveLightingPanel(uint8_t pin, uint16_t width, uint16_t height, neoPixelType type) {
    m_pin = pin;
    m_width = width;
    m_height = height;
    m_neoPixel = Adafruit_NeoPixel(m_width * m_height, m_pin, type);
}

void RoveLightingPanel::begin() {
    m_neoPixel.begin();
    m_neoPixel.setBrightness(m_maxBrightness);
}

void RoveLightingPanel::fill(Color color) {
    m_neoPixel.fill(Adafruit_NeoPixel::Color(color.r, color.g, color.b));
}

void RoveLightingPanel::clear() {
    m_neoPixel.clear();
}

uint32_t RoveLightingPanel::getPixelID(int32_t x, int32_t y) const {
    // Check if out of bounds
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) return -1;
    // Flip coordinates before calculation to account for orientation
    switch (m_orientation) {
        // Normal x
        case LightingPanelOrientation::TOP_LEFT:
            if (y % 2 == 0) x = m_width - x - 1;
            break;
        // Flip x
        case LightingPanelOrientation::TOP_RIGHT:
            if (y % 2 == 1) x = m_width - x - 1;
            break;
        // Normal x, Flip y
        case LightingPanelOrientation::BOTTOM_LEFT:
            if (y % 2 == 0) x = m_width - x - 1;
            y = m_height - y - 1;
            break;
        // Flip x and y
        case LightingPanelOrientation::BOTTOM_RIGHT:
            if (y % 2 == 1) x = m_width - x - 1;
            y = m_height - y - 1;
            break;
    }

    uint32_t pixelID = y * m_height + x;

    // Correct for skipping over dead pixels
    for (int i = 0; i < m_deadPixelCount; i++) {
        if (m_deadPixels[i] == pixelID) return; // Do not attempt to set this pixel
        if (m_deadPixels[i] < pixelID) --pixelID; // Pixel will be reached earlier than expected.
    }

    return pixelID;
}

void RoveLightingPanel::setPixelRGB(int32_t x, int32_t y, Color color) {
    // Skip if transparent
    if (color.transparent) return;

    int pixelID = getPixelID(x, y);
    if (pixelID == -1) return; // Out of bounds

    m_neoPixel.setPixelColor(pixelID, color.r, color.g, color.b);
}

void RoveLightingPanel::setPixelGrayscale(int32_t x, int32_t y, uint8_t value) {
    int pixelID = 256 - (8 * x) + (x % 2 == 0 ? -8 + y : -y - 1);
    m_neoPixel.setPixelColor(pixelID, value, value, value);
}

void RoveLightingPanel::configOrientation(LightingPanelOrientation orientation) { m_orientation = orientation; }

void RoveLightingPanel::configMaxBrightness(uint8_t brightness) {
    m_maxBrightness = brightness;
    if (m_neoPixel.getBrightness() > m_maxBrightness) {
        m_neoPixel.setBrightness(m_maxBrightness);
    }
}
void RoveLightingPanel::setBrightness(uint8_t brightness) {
    if (brightness <= m_maxBrightness) {
        m_neoPixel.setBrightness(brightness);
    } else {
        m_neoPixel.setBrightness(m_maxBrightness);
    }
}

void RoveLightingPanel::registerDeadPixel(uint32_t pixelID) {
    if (m_deadPixelCount < MAX_DEAD_PIXELS) {
        m_deadPixels[m_deadPixelCount++] = pixelID;
    }
}
