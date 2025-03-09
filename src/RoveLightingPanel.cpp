#include "RoveLightingPanel.h"

RoveLightingPanel::RoveLightingPanel(uint8_t pin, uint16_t width, uint16_t height, neoPixelType type) {
    m_width = width;
    m_height = height;
    m_neoPixel = new Adafruit_NeoPixel(m_width * m_height, pin, type);
}

RoveLightingPanel::RoveLightingPanel(Adafruit_NeoPixel *neoPixel, uint16_t width, uint16_t height) {
    m_neoPixel = neoPixel;
    m_width = width;
    m_height = height;
}

RoveLightingPanel::~RoveLightingPanel() {
    delete m_neoPixel;
}

void RoveLightingPanel::begin() {
    if (!m_neoPixel) return;
    configBrightness(m_brightness);
    m_neoPixel->begin();
    m_neoPixel->show();
}

void RoveLightingPanel::show() {
    if (!m_neoPixel) return;
    m_neoPixel->show();
}

void RoveLightingPanel::fill(Color color) {
    if (!m_neoPixel) return;
    m_neoPixel->fill(Adafruit_NeoPixel::Color(color.r, color.g, color.b));
}

void RoveLightingPanel::clear() {
    if (!m_neoPixel) return;
    m_neoPixel->clear();
}

int32_t RoveLightingPanel::getPixelID(int32_t x, int32_t y) const {
    if (!m_neoPixel) return;
    // Check if out of bounds
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) return -1;
    
    // Flip coordinates before calculation to account for orientation
    uint16_t width = m_width;
    uint16_t height = m_height;

    if (m_orientation & ORIENTATION_IS_INVERTED) {
        // Swap X and Y
        int32_t temp = x;
        x = y;
        y = temp;
        // Swap width and height
        width = m_height;
        height = m_width;
    }
    
    if (m_orientation & ORIENTATION_IS_FLIPPED_Y) {
        y = height - y - 1;
    }

    if (m_orientation & ORIENTATION_IS_FLIPPED_X) {
        if (y % 2 == 0) x = width - x - 1;
    } else {
        // Because of the zig-zag pattern, X gets flipped on odd rows under normal operation
        if (y % 2 == 1) x = width - x - 1;
    }

    int32_t pixelID = y * width + x;

    // Correct for skipping over dead pixels
    for (int i = 0; i < m_deadPixelCount; i++) {
        if (m_deadPixels[i] == pixelID) return -1; // Do not attempt to set this pixel
        if (m_deadPixels[i] < pixelID) --pixelID; // Pixel will be reached earlier than expected
    }

    return pixelID;
}

void RoveLightingPanel::setPixelRGB(int32_t x, int32_t y, Color color) {
    if (!m_neoPixel) return;
    // Skip if transparent
    if (color.transparent) return;

    int pixelID = getPixelID(x, y);
    if (pixelID == -1) return; // Out of bounds

    m_neoPixel->setPixelColor(pixelID, color.r, color.g, color.b);
}

void RoveLightingPanel::setPixelGrayscale(int32_t x, int32_t y, uint8_t value) {
    if (!m_neoPixel) return;
    int pixelID = 256 - (8 * x) + (x % 2 == 0 ? -8 + y : -y - 1);
    m_neoPixel->setPixelColor(pixelID, value, value, value);
}

void RoveLightingPanel::configOrientation(LightingPanelOrientation orientation) {
    m_orientation = orientation;
}

void RoveLightingPanel::configBrightness(uint8_t brightness) {
    m_brightness = brightness;
    if (!m_neoPixel) return;
    m_neoPixel->setBrightness(m_brightness);
}

void RoveLightingPanel::configDeadPixel(uint32_t pixelID) {
    if (m_deadPixelCount < MAX_DEAD_PIXELS) {
        m_deadPixels[m_deadPixelCount++] = pixelID;
    }
}

void RoveLightingPanel::setNeoPixel(Adafruit_NeoPixel *neoPixel) {
    if (m_neoPixel) {
        delete m_neoPixel;
    }
    m_neoPixel = neoPixel;
}
