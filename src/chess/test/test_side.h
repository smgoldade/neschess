/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include <chess/side.h>

auto constexpr test_side() noexcept -> bool {
    static_assert(opposing_side(Side::NONE) == Side::NONE, "Side::NONE opposes Side::NONE");
    static_assert(opposing_side(Side::WHITE) == Side::BLACK, "Side::BLACK opposes Side::WHITE");
    static_assert(opposing_side(Side::BLACK) == Side::WHITE, "Side::WHITE opposes Side::BLACK");

    return true;
}