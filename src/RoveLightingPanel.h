#ifndef ROVELIGHTINGPANEL_H
#define ROVELIGHTINGPANEL_H

#include <Adafruit_NeoPixel.h>

#include "RoveLightingUtils.h"
#include "RoveCanvas.h"

#define MAX_DEAD_PIXELS 32

/**
 * @brief Describes the location of the zeroth pixel on the panel
 * 
 */
enum class LightingPanelOrientation {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
};

class RoveLightingPanel : public RoveCanvas {
private:
    Adafruit_NeoPixel m_neoPixel;

    uint8_t m_pin;
    uint16_t m_width, m_height;

    uint8_t m_maxBrightness = 70;

    uint8_t m_deadPixelCount = 0;
    uint32_t m_deadPixels[MAX_DEAD_PIXELS] = {0};

    LightingPanelOrientation m_orientation = LightingPanelOrientation::TOP_LEFT;

public:
    /**
     * @brief Construct a new Rove Lighting Panel object
     * 
     * @param pin The pin the signal wire of the panel is connected to
     * @param width The width of the panel in pixels
     * @param height The height of the panel in pixels
     */
    RoveLightingPanel(uint8_t pin, uint16_t width, uint16_t height, neoPixelType type = NEO_GRB + NEO_KHZ800);

    void begin();

    uint32_t getPixelID(int32_t x, int32_t y) const;

    void fill(Color color) override;
    void clear() override;
    void setPixelRGB(int32_t x, int32_t y, Color color) override;
    void setPixelGrayscale(int32_t x, int32_t y, uint8_t value) override;

    void configOrientation(LightingPanelOrientation orientation);
    void configMaxBrightness(uint8_t brightness);
    void setBrightness(uint8_t brightness);
    void registerDeadPixel(uint32_t pixelID);

    const Adafruit_NeoPixel &getNeoPixel() const { return m_neoPixel; }
    uint16_t getWidth() const { return m_width; }
    uint16_t getHeight() const { return m_height; }
    uint8_t getMaxBrightness() const { return m_maxBrightness; }
};

#endif // ROVELIGHTINGPANEL_H
