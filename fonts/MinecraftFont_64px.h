#ifndef MINECRAFT_FONT_H
#define MINECRAFT_FONT_H

#include "../src/RoveLightingUtils.h"

#include "../fonts/MinecraftBold_64px.h"
inline Font *LoadMinecraftBold() {
    Font *MinecraftBold = new Font {
        64, 64,
        ' ', '~',
    };
    const uint8_t **letterData = new const uint8_t*[95];
    for (int i = 0; i < 95; i++) {
        letterData[i] = minecraft_bold_64px_data[i];
    }
    MinecraftBold->letterData = letterData;
    MinecraftBold->letterWidths = minecraft_bold_64px_letter_widths;
    return MinecraftBold;
}
#include "../fonts/MinecraftRegular_64px.h"
inline Font *LoadMinecraftRegular() {
    Font *MinecraftRegular = new Font {
        64, 64,
        ' ', '~',
    };
    const uint8_t **letterData = new const uint8_t*[95];
    for (int i = 0; i < 95; i++) {
        letterData[i] = minecraft_regular_64px_data[i];
    }
    MinecraftRegular->letterData = letterData;
    MinecraftRegular->letterWidths = minecraft_regular_64px_letter_widths;
    return MinecraftRegular;
}
inline FontSet LoadMinecraftFont() {
    Font *regular = LoadMinecraftRegular();
    Font *bold = LoadMinecraftBold();
    Font *italic = regular;
    return FontSet{regular, bold, italic};
}

#endif // MINECRAFT_FONT_H
