#ifndef ROVELIGHTINGPANEL_H
#define ROVELIGHTINGPANEL_H

#include <Adafruit_NeoPixel.h>

#include "RoveLightingUtils.h"
#include "RoveCanvas.h"

#define MAX_DEAD_PIXELS 32

// Indicates that X should be flipped before rendering
#define ORIENTATION_IS_FLIPPED_X (1 << 0)
// Indicates that Y should be flipped before rendering
#define ORIENTATION_IS_FLIPPED_Y (1 << 1)
// Indicates X and Y should be swapped before rendering
#define ORIENTATION_IS_INVERTED (1 << 2)

/**
 * @brief Describes the location of the zeroth pixel on the panel and the direction of winding.
 * To determine which value to use, look at the LED array for an arrow in the corner that indicates the direction
 */
enum LightingPanelOrientation {
    TOP_LEFT_THEN_RIGHT     = 0,
    TOP_RIGHT_THEN_LEFT     = ORIENTATION_IS_FLIPPED_X,
    BOTTOM_LEFT_THEN_RIGHT  = ORIENTATION_IS_FLIPPED_Y,
    BOTTOM_RIGHT_THEN_LEFT  = ORIENTATION_IS_FLIPPED_X | ORIENTATION_IS_FLIPPED_Y,
    TOP_LEFT_THEN_DOWN      = ORIENTATION_IS_INVERTED,
    BOTTOM_LEFT_THEN_UP     = ORIENTATION_IS_INVERTED | ORIENTATION_IS_FLIPPED_X,
    TOP_RIGHT_THEN_DOWN     = ORIENTATION_IS_INVERTED | ORIENTATION_IS_FLIPPED_Y,
    BOTTOM_RIGHT_THEN_UP    = ORIENTATION_IS_INVERTED | ORIENTATION_IS_FLIPPED_X | ORIENTATION_IS_FLIPPED_Y,
};

class RoveLightingPanel : public RoveCanvas {
private:
    Adafruit_NeoPixel *m_neoPixel = nullptr;

    uint8_t m_pin;
    uint16_t m_width, m_height;

    uint8_t m_brightness = 70;

    uint8_t m_deadPixelCount = 0;
    uint32_t m_deadPixels[MAX_DEAD_PIXELS] = {0};

    LightingPanelOrientation m_orientation = LightingPanelOrientation::TOP_RIGHT_THEN_LEFT;

public:
    RoveLightingPanel(uint8_t pin, uint16_t width, uint16_t height, neoPixelType type = NEO_GRB + NEO_KHZ800);
    RoveLightingPanel(Adafruit_NeoPixel *neoPixel, uint16_t width, uint16_t height);
    RoveLightingPanel(const RoveLightingPanel &other) = delete;
    ~RoveLightingPanel();

    void begin();

    int32_t getPixelID(int32_t x, int32_t y) const;

    void show() override;
    void fill(Color color) override;
    void clear() override;
    void setPixelColor(int32_t x, int32_t y, Color color) override;
    void setPixelRGB(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b) override;
    void setPixelRGBA(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void setPixelGrayscale(int32_t x, int32_t y, uint8_t value) override;

    void configOrientation(LightingPanelOrientation orientation);
    void configBrightness(uint8_t brightness);
    void configDeadPixel(uint32_t pixelID);

    void setNeoPixel(Adafruit_NeoPixel *neoPixel);
    const Adafruit_NeoPixel &getNeoPixel() const { return *m_neoPixel; }
    uint16_t getWidth() const { return m_width; }
    uint16_t getHeight() const { return m_height; }
    uint8_t getBrightness() const { return m_brightness; }

};

#endif // ROVELIGHTINGPANEL_H
