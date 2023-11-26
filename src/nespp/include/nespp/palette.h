/**
* @author Steven Goldade
* @date 9/4/2023
*/
#pragma once
#include "low_level.h"
#include "types.h"

namespace nespp {
    class Color {
    public:
        enum Value : u8 {
            DARK_GRAY = 0x00,
            DARK_AZURE = 0x01,
            DARK_BLUE = 0x02,
            DARK_VIOLET = 0x03,
            DARK_MAGENTA = 0x04,
            DARK_ROSE = 0x05,
            DARK_RED = 0x06,
            DARK_ORANGE = 0x07,
            DARK_OLIVE = 0x08,
            DARK_CHARTREUSE = 0x09,
            DARK_GREEN = 0x0A,
            DARK_SPRING = 0x0B,
            DARK_CYAN = 0x0C,
            /**
             * Should be avoided, outputs a voltage that would indicate "blacker than black"
             */
            ULTRA_BLACK = 0x0D,
            MIRROR_BLACK = 0x0E,
            BLACK = 0x0F,
            MEDIUM_GRAY = 0x10,
            MEDIUM_AZURE = 0x11,
            MEDIUM_BLUE = 0x12,
            MEDIUM_VIOLET = 0x13,
            MEDIUM_MAGENTA = 0x14,
            MEDIUM_ROSE = 0x15,
            MEDIUM_RED = 0x16,
            MEDIUM_ORANGE = 0x17,
            MEDIUM_OLIVE = 0x18,
            MEDIUM_CHARTREUSE = 0x19,
            MEDIUM_GREEN = 0x1A,
            MEDIUM_SPRING = 0x1B,
            MEDIUM_CYAN = 0x1C,
            MIRROR_BLACK_2 = 0x1D,
            MIRROR_BLACK_3 = 0x1E,
            MIRROR_BLACK_4 = 0x1F,
            WHITE = 0x20,
            LIGHT_AZURE = 0x21,
            LIGHT_BLUE = 0x22,
            LIGHT_VIOLET = 0x23,
            LIGHT_MAGENTA = 0x24,
            LIGHT_ROSE = 0x25,
            LIGHT_RED = 0x26,
            LIGHT_ORANGE = 0x27,
            LIGHT_OLIVE = 0x28,
            LIGHT_CHARTREUSE = 0x29,
            LIGHT_GREEN = 0x2A,
            LIGHT_SPRING = 0x2B,
            LIGHT_CYAN = 0x2C,
            MIRROR_DARK_GRAY = 0x2D,
            MIRROR_BLACK_5 = 0x2E,
            MIRROR_BLACK_6 = 0x2F,
            /**
             * Fades to black slower than standard white
             */
            ULTRA_WHITE = 0x30,
            PALE_AZURE = 0x31,
            PALE_BLUE = 0x32,
            PALE_VIOLET = 0x33,
            PALE_MAGENTA = 0x34,
            PALE_ROSE = 0x35,
            PALE_RED = 0x36,
            PALE_ORANGE = 0x37,
            PALE_OLIVE = 0x38,
            PALE_CHARTREUSE = 0x39,
            PALE_GREEN = 0x3A,
            PALE_SPRING = 0x3B,
            PALE_CYAN = 0x3C,
            MIRROR_MEDIUM_GRAY = 0x3D,
            MIRROR_BLACK_7 = 0x3E,
            MIRROR_BLACK_8 = 0x3F
        };
        constexpr Color() : value(Value::BLACK) {}
        constexpr Color(const Value _value) : value(_value) {} // NOLINT(*-explicit-constructor)

        constexpr operator Value() const { return value; } // NOLINT(*-explicit-constructor)
        constexpr explicit operator bool() const = delete;

        [[nodiscard]] auto constexpr darken() const -> Color {
            switch(value) {
                case DARK_GRAY:
                case DARK_AZURE:
                case DARK_BLUE:
                case DARK_VIOLET:
                case DARK_MAGENTA:
                case DARK_ROSE:
                case DARK_RED:
                case DARK_ORANGE:
                case DARK_OLIVE:
                case DARK_CHARTREUSE:
                case DARK_GREEN:
                case DARK_SPRING:
                case DARK_CYAN:
                case ULTRA_BLACK:
                case MIRROR_BLACK:
                case BLACK:
                case MIRROR_BLACK_2:
                case MIRROR_BLACK_3:
                case MIRROR_BLACK_4:
                case MIRROR_BLACK_5:
                case MIRROR_BLACK_6:
                case MIRROR_DARK_GRAY:
                case MIRROR_BLACK_7:
                case MIRROR_BLACK_8:
                    return BLACK;
                case MEDIUM_GRAY:
                case MIRROR_MEDIUM_GRAY:
                    return DARK_GRAY;
                case MEDIUM_AZURE:
                    return DARK_AZURE;
                case MEDIUM_BLUE:
                    return DARK_BLUE;
                case MEDIUM_VIOLET:
                    return DARK_VIOLET;
                case MEDIUM_MAGENTA:
                    return DARK_MAGENTA;
                case MEDIUM_ROSE:
                    return DARK_ROSE;
                case MEDIUM_RED:
                    return DARK_RED;
                case MEDIUM_ORANGE:
                    return DARK_ORANGE;
                case MEDIUM_OLIVE:
                    return DARK_OLIVE;
                case MEDIUM_CHARTREUSE:
                    return DARK_CHARTREUSE;
                case MEDIUM_GREEN:
                    return DARK_GREEN;
                case MEDIUM_SPRING:
                    return DARK_SPRING;
                case MEDIUM_CYAN:
                    return DARK_CYAN;
                case WHITE:
                    return MEDIUM_GRAY;
                case LIGHT_AZURE:
                    return MEDIUM_AZURE;
                case LIGHT_BLUE:
                    return MEDIUM_BLUE;
                case LIGHT_VIOLET:
                    return MEDIUM_VIOLET;
                case LIGHT_MAGENTA:
                    return MEDIUM_MAGENTA;
                case LIGHT_ROSE:
                    return MEDIUM_ROSE;
                case LIGHT_RED:
                    return MEDIUM_RED;
                case LIGHT_ORANGE:
                    return MEDIUM_ORANGE;
                case LIGHT_OLIVE:
                    return MEDIUM_OLIVE;
                case LIGHT_CHARTREUSE:
                    return MEDIUM_CHARTREUSE;
                case LIGHT_GREEN:
                    return MEDIUM_GREEN;
                case LIGHT_SPRING:
                    return MEDIUM_SPRING;
                case LIGHT_CYAN:
                    return MEDIUM_CYAN;
                case ULTRA_WHITE:
                    return WHITE;
                case PALE_AZURE:
                    return LIGHT_AZURE;
                case PALE_BLUE:
                    return LIGHT_BLUE;
                case PALE_VIOLET:
                    return LIGHT_VIOLET;
                case PALE_MAGENTA:
                    return LIGHT_MAGENTA;
                case PALE_ROSE:
                    return LIGHT_ROSE;
                case PALE_RED:
                    return LIGHT_RED;
                case PALE_ORANGE:
                    return LIGHT_ORANGE;
                case PALE_OLIVE:
                    return LIGHT_OLIVE;
                case PALE_CHARTREUSE:
                    return LIGHT_CHARTREUSE;
                case PALE_GREEN:
                    return LIGHT_GREEN;
                case PALE_SPRING:
                    return LIGHT_SPRING;
                case PALE_CYAN:
                    return LIGHT_CYAN;
            }
        }

        [[nodiscard]] auto constexpr lighten() const -> Color {
            switch(value) {
                case DARK_GRAY:
                case MIRROR_DARK_GRAY:
                    return MEDIUM_GRAY;
                case DARK_AZURE:
                    return MEDIUM_AZURE;
                case DARK_BLUE:
                    return MEDIUM_BLUE;
                case DARK_VIOLET:
                    return MEDIUM_VIOLET;
                case DARK_MAGENTA:
                    return MEDIUM_MAGENTA;
                case DARK_ROSE:
                    return MEDIUM_ROSE;
                case DARK_RED:
                    return MEDIUM_RED;
                case DARK_ORANGE:
                    return MEDIUM_ORANGE;
                case DARK_OLIVE:
                    return MEDIUM_OLIVE;
                case DARK_CHARTREUSE:
                    return MEDIUM_CHARTREUSE;
                case DARK_GREEN:
                    return MEDIUM_GREEN;
                case DARK_SPRING:
                    return MEDIUM_SPRING;
                case DARK_CYAN:
                    return MEDIUM_CYAN;
                case ULTRA_BLACK:
                case MIRROR_BLACK:
                case BLACK:
                case MIRROR_BLACK_2:
                case MIRROR_BLACK_3:
                case MIRROR_BLACK_4:
                case MIRROR_BLACK_5:
                case MIRROR_BLACK_6:
                case MIRROR_BLACK_7:
                case MIRROR_BLACK_8:
                    return DARK_GRAY;
                case MEDIUM_GRAY:
                case MIRROR_MEDIUM_GRAY:
                    return WHITE;
                case MEDIUM_AZURE:
                    return LIGHT_AZURE;
                case MEDIUM_BLUE:
                    return LIGHT_BLUE;
                case MEDIUM_VIOLET:
                    return LIGHT_VIOLET;
                case MEDIUM_MAGENTA:
                    return LIGHT_MAGENTA;
                case MEDIUM_ROSE:
                    return LIGHT_ROSE;
                case MEDIUM_RED:
                    return LIGHT_RED;
                case MEDIUM_ORANGE:
                    return LIGHT_ORANGE;
                case MEDIUM_OLIVE:
                    return LIGHT_OLIVE;
                case MEDIUM_CHARTREUSE:
                    return LIGHT_CHARTREUSE;
                case MEDIUM_GREEN:
                    return LIGHT_GREEN;
                case MEDIUM_SPRING:
                    return LIGHT_SPRING;
                case MEDIUM_CYAN:
                    return LIGHT_CYAN;
                case WHITE:
                case ULTRA_WHITE:
                case PALE_AZURE:
                case PALE_BLUE:
                case PALE_VIOLET:
                case PALE_MAGENTA:
                case PALE_ROSE:
                case PALE_RED:
                case PALE_ORANGE:
                case PALE_OLIVE:
                case PALE_CHARTREUSE:
                case PALE_GREEN:
                case PALE_SPRING:
                case PALE_CYAN:
                    return ULTRA_WHITE;
                case LIGHT_AZURE:
                    return PALE_AZURE;
                case LIGHT_BLUE:
                    return PALE_BLUE;
                case LIGHT_VIOLET:
                    return PALE_VIOLET;
                case LIGHT_MAGENTA:
                    return PALE_MAGENTA;
                case LIGHT_ROSE:
                    return PALE_ROSE;
                case LIGHT_RED:
                    return PALE_RED;
                case LIGHT_ORANGE:
                    return PALE_ORANGE;
                case LIGHT_OLIVE:
                    return PALE_OLIVE;
                case LIGHT_CHARTREUSE:
                    return PALE_CHARTREUSE;
                case LIGHT_GREEN:
                    return PALE_GREEN;
                case LIGHT_SPRING:
                    return PALE_SPRING;
                case LIGHT_CYAN:
                    return PALE_CYAN;
            }
        }
    private:
        Value value;
    };

    struct ColorGroup {
        // The background color is shared on all palette entries
        Color color_1;
        Color color_2;
        Color color_3;

        auto constexpr darken() -> void {
            color_1 = color_1.darken();
            color_2 = color_2.darken();
            color_3 = color_3.darken();
        }

        auto constexpr lighten() -> void {
            color_1 = color_1.darken();
            color_2 = color_2.darken();
            color_3 = color_3.darken();
        }

        [[nodiscard]] auto constexpr all(Color color) const -> bool {
            return (color_1 == color_2) && (color_2 == color_3) && (color_3 == color);
        }
    };

    struct Palette {
        Color background_color;
        ColorGroup palette_0;
        Color background_color_1;
        ColorGroup palette_1;
        Color background_color_2;
        ColorGroup palette_2;
        Color background_color_3;
        ColorGroup palette_3;
        
        [[nodiscard]] auto constexpr darken() const noexcept -> Palette {
            Palette newPalette = *this;
            newPalette.background_color = newPalette.background_color.darken();
            newPalette.palette_0.darken();
            newPalette.background_color_1 = newPalette.background_color_1.darken();
            newPalette.palette_1.darken();
            newPalette.background_color_2 = newPalette.background_color_2.darken();
            newPalette.palette_2.darken();
            newPalette.background_color_3 = newPalette.background_color_3.darken();
            newPalette.palette_3.darken();
            return newPalette;
        }
    };
}


