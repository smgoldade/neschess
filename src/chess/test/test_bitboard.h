/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include <chess/bitboard.h>

auto constexpr test_bitboard() noexcept -> bool {
    using namespace chess;
    auto constexpr white_pawns   = Bitboard(0x000000000000FF00);
    auto constexpr white_knights = Bitboard(0x0000000000000042);

    static_assert(white_pawns.is_set(Square::A2));
    static_assert(white_pawns.is_set(Square::B2));
    static_assert(white_pawns.is_set(Square::C2));
    static_assert(white_pawns.is_set(Square::D2));
    static_assert(white_pawns.is_set(Square::E2));
    static_assert(white_pawns.is_set(Square::F2));
    static_assert(white_pawns.is_set(Square::G2));
    static_assert(white_pawns.is_set(Square::H2));

    static_assert(white_knights.is_set(Square::B1));
    static_assert(white_knights.is_set(Square::G1));
    return true;
}