/**
 * @author Steven Goldade
 * @date 11/11/2023
 */
#include "test_bitboard.h"
#include "test_board.h"
#include "test_move.h"
#include "test_move_generator.h"
#include "test_piece.h"
#include "test_position.h"
#include "test_side.h"
#include "test_square.h"

int main() {
    static_assert(test_side(), "Side");
    static_assert(test_piece(), "Piece");
    static_assert(test_square(), "Square");
    static_assert(test_bitboard(), "Bitboard");
    static_assert(test_move(), "Move");
    static_assert(test_board(), "Board");
    static_assert(test_position(), "Position");
    static_assert(test_move_generator(), "Move Generator");

    return 0;
}