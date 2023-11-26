// Author: Steven Goldade
#pragma once
#include "nespp/include/nespp/types.h"

namespace Tileset0 {
    static constexpr u8 PALETTE_0 = 0x00;
    static constexpr u8 PALETTE_1 = 0x01;
    static constexpr u8 PALETTE_2 = 0x02;
    static constexpr u8 PALETTE_3 = 0x03;
    
    static constexpr u8 ARROW_LEFT = 0x08;

    // Border
    static constexpr u8 BORDER_TOP_LEFT = 0x04;
    static constexpr u8 BORDER_TOP_CENTER = 0x05;
    static constexpr u8 BORDER_TOP_RIGHT = 0x06;
    static constexpr u8 BORDER_RIGHT = 0x07;
    static constexpr u8 BORDER_BOTTOM_LEFT = 0x14;
    static constexpr u8 BORDER_BOTTOM_CENTER = 0x15;
    static constexpr u8 BORDER_BOTTOM_RIGHT = 0x16;
    static constexpr u8 BORDER_LEFT = 0x17;

    // Small pieces
    static constexpr u8 SMALL_PAWN = 0x1A;
    static constexpr u8 SMALL_KNIGHT = 0x1B;
    static constexpr u8 SMALL_BISHOP = 0x1C;
    static constexpr u8 SMALL_ROOK = 0x1D;
    static constexpr u8 SMALL_QUEEN = 0x1E;
    static constexpr u8 SMALL_KING = 0x1F;

    // Full size pieces
    static constexpr u8 WHITE_PAWN = 0x80;
    static constexpr u8 WHITE_KNIGHT = 0x82;
    static constexpr u8 WHITE_BISHOP = 0x84;
    static constexpr u8 WHITE_ROOK = 0x86;
    static constexpr u8 WHITE_QUEEN = 0x88;
    static constexpr u8 WHITE_KING = 0x8A;
    static constexpr u8 BLACK_PAWN = 0xA0;
    static constexpr u8 BLACK_KNIGHT = 0xA2;
    static constexpr u8 BLACK_BISHOP = 0xA4;
    static constexpr u8 BLACK_ROOK = 0xA6;
    static constexpr u8 BLACK_QUEEN = 0xA8;
    static constexpr u8 BLACK_KING = 0xAA;
}// namespace Tileset0

namespace Tileset1 {
    static constexpr u8 HOURGLASS = 0xA0;
    static constexpr u8 HOURGLASS_90 = 0xA1;
    static constexpr u8 OUTER_BORDER = 0xA2;
    
    static constexpr u8 UPPERCASE_T = 0xA3;
    static constexpr u8 LOWERCASE_H = 0xA4;
    static constexpr u8 LOWERCASE_I = 0xA5;
    static constexpr u8 LOWERCASE_N = 0xA6;
    static constexpr u8 LOWERCASE_K = 0xA7;
    static constexpr u8 LOWERCASE_G = 0xA8;
    
    static constexpr u8 WHITE_PAWN = 0xB0;
    static constexpr u8 WHITE_KNIGHT = 0xB2;
    static constexpr u8 WHITE_BISHOP = 0xB4;
    static constexpr u8 WHITE_ROOK = 0xB6;
    static constexpr u8 WHITE_QUEEN = 0xB8;
    static constexpr u8 WHITE_KING = 0xBA;
    static constexpr u8 BLACK_PAWN = 0xD0;
    static constexpr u8 BLACK_KNIGHT = 0xD2;
    static constexpr u8 BLACK_BISHOP = 0xD4;
    static constexpr u8 BLACK_ROOK = 0xD6;
    static constexpr u8 BLACK_QUEEN = 0xD8;
    static constexpr u8 BLACK_KING = 0xDA;
}// namespace Tileset1
