/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include <nespp/types.h>

namespace chess {
    enum class Side : u8 {
        NONE = 0,
        WHITE = 1,
        BLACK = 2
    };
    auto constexpr opposing_side(Side side) -> Side {
        switch(side) {
            case Side::NONE:
                return Side::NONE;
            case Side::WHITE:
                return Side::BLACK;
            case Side::BLACK:
                return Side::WHITE;
        }
    }
}// namespace chess
