#ifndef ROVEPAINTER_H
#define ROVEPAINTER_H

#include "RoveCanvas.h"
#include "RoveLightingUtils.h"

#define LETTER_SPACING 1

class RovePainter {
private:
    RoveCanvas *m_canvas = nullptr;
    FontSet *m_font = nullptr;

public:
    RovePainter() {}
    RovePainter(RoveCanvas *canvas) : m_canvas(canvas) {}

    void drawImage(const Image &image, int32_t x, int32_t y);

    void drawText(const char *message, int32_t x, int32_t y);

    void setCanvas(RoveCanvas *canvas) { m_canvas = canvas; }

    void setFont(Font *font) { delete m_font; m_font = new FontSet{font, font, font}; }
    void setFont(FontSet *font) { m_font = font; }

private:
    class TextReader;

};

// Iterator for reading text
class RovePainter::TextReader {
public:
    const char *text;
    const uint32_t length;
    FontSet *font;
    uint32_t pos = 0; // current slice of text

    char currentChar = '?';

    bool bold = false;
    bool italic = false;
    bool underline = false;
    bool strike = false;

    Color color = WHITE;
    Color highlight = TRANSPARENT;

    TextReader(const char *text, uint32_t length, FontSet *font) : text(text), length(length), font(font) {}

    bool next();
    void reset();
    operator bool() const { return pos < length; }

private:
    const uint8_t *lookupCharacter(char ascii);
    int lookupCharacterWidth(char ascii);
    static int convertHex(char c);

    friend class RovePainter;
};

#endif // ROVEPAINTER_H
