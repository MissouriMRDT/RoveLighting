#include "RovePainter.h"

void RovePainter::drawImage(const Image &image, int32_t xPos, int32_t yPos) {
    if (!m_canvas) return;
    if (!image.dataPtr) return;

    const uint8_t *pixel = image.dataPtr;
    for (int32_t y = yPos; y < yPos + (int32_t)image.height; y++) {
        for (int32_t x = xPos; x < xPos + (int32_t)image.width; x++) {
            m_canvas->setPixelRGB(x, y, pixel[0], pixel[1], pixel[2]);
            pixel += 3;
        }
    }
}

void RovePainter::drawText(const char *message, int32_t x, int32_t y) {
    if (!m_font) return;
    int length = 0;
    while (message[length]) length++;
    TextReader reader(message, length, m_font);
    while (reader.next()) {
        Font *font = reader.bold ? m_font->fontBold : m_font->fontRegular;
        int letterWidth = reader.lookupCharacterWidth(reader.currentChar);
        const uint8_t *letterData = reader.lookupCharacter(reader.currentChar);
        for (int32_t u = 0; u < letterWidth; u++) {
            for (int32_t v = 0; v < font->letterHeight; v++) {
                if (letterData[v * letterWidth + u] == 1) {
                    m_canvas->setPixelColor(x + u, y + v, reader.color);
                } else {
                    m_canvas->setPixelColor(x + u, y + v, reader.highlight);
                }
            }
        }
        x += letterWidth + LETTER_SPACING;
    }
}

bool RovePainter::TextReader::next() {
    if (pos >= length) return false;
    while (pos < length && text[pos] == '\\') { // allow multiple consecutive escape sequences
        if (++pos < length)
        switch (text[pos]) {
            case '\\':
                // do nothing I guess
                break;
            case 'b':
                if (++pos < length) {
                    if (text[pos] == '0') bold = true;
                    else if (text[pos] == '1') bold = false;
                }
                break;
            case 'i':
                if (++pos < length) {
                    if (text[pos] == '0') italic = true;
                    else if (text[pos] == '1') italic = false;
                }
                break;
            case 'u':
                if (++pos < length) {
                    if (text[pos] == '0') underline = true;
                    else if (text[pos] == '1') underline = false;
                }
                break;
            case 's':
                if (++pos < length) {
                    if (text[pos] == '0') strike = true;
                    else if (text[pos] == '1') strike = false;
                }
                break;
            case 'c':
                if (++pos < length) {
                    if (text[pos] == '0') {
                        color = WHITE;
                        ++pos; // skip semicolon
                    } else if (text[pos] == '#') {
                        uint32_t readColor = 0;
                        for (int i = 0; ++pos < length && i < 7; i++) {
                            if (text[pos] == ';') break;
                            int hexVal = convertHex(text[pos]);
                            if (hexVal == -1) break;
                            readColor |= hexVal << ((5 - i) * 4);
                        }
                        color.r = readColor >> 16 & 0xFF;
                        color.g = readColor >> 8  & 0xFF;
                        color.b = readColor >> 0  & 0xFF;
                        color.transparent = false;
                    } // TODO: support rgb
                }
                break;
            case 'h':
                if (++pos < length) {
                    if (text[pos] == '0') {
                        highlight = TRANSPARENT;
                        ++pos; // skip semicolon
                    } else if (text[pos] == '#') {
                        uint32_t readColor = 0;
                        for (int i = 0; ++pos < length && i < 7; i++) {
                            if (text[pos] == ';') break;
                            int hexVal = convertHex(text[pos]);
                            if (hexVal == -1) break;
                            readColor |= hexVal << ((5 - i) * 4);
                        }
                        highlight.r = readColor >> 16 & 0xFF;
                        highlight.g = readColor >> 8  & 0xFF;
                        highlight.b = readColor >> 0  & 0xFF;
                        highlight.transparent = false;
                    } // TODO: support rgb
                }
                break;
        }
        ++pos; // skip last escape character
    }
    if (pos < length) currentChar = text[pos];
    ++pos;
    return pos <= length;
}

void RovePainter::TextReader::reset() {
    pos = 0;
    currentChar = '?';
    bold = false;
    italic = false;
    underline = false;
    strike = false;
    color = WHITE;
    highlight = TRANSPARENT;
}

const uint8_t *RovePainter::TextReader::lookupCharacter(char ascii) {
    if (ascii < font->fontRegular->firstChar || ascii > font->fontRegular->lastChar) return nullptr;
    if (bold) return font->fontBold->letterData[ascii - font->fontBold->firstChar];
    else if (italic) return font->fontItalic->letterData[ascii - font->fontItalic->firstChar];
    else return font->fontRegular->letterData[ascii - font->fontRegular->firstChar];
}

int RovePainter::TextReader::lookupCharacterWidth(char ascii) {
    if (ascii < font->fontRegular->firstChar || ascii > font->fontRegular->lastChar) ascii = '?';
    if (bold) return font->fontBold->letterWidths[ascii - font->fontBold->firstChar];
    else if (italic) return font->fontItalic->letterWidths[ascii - font->fontItalic->firstChar];
    else return font->fontRegular->letterWidths[ascii - font->fontRegular->firstChar];
}

int RovePainter::TextReader::convertHex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 0xa;
    if (c >= 'A' && c <= 'F') return c - 'A' + 0xA;
    return -1;
}
