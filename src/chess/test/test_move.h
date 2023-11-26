/**
* @author Steven Goldade
* @date 11/12/2023
*/
#include <chess/move.h>

using namespace chess;

auto constexpr test_move() -> bool {
    static_assert(Move().is_null_move(), "Default constructor is null move");

    static_assert(Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH).from_square() == Square::E2);
    static_assert(Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH).to_square() == Square::E4);
    static_assert(Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH).flags() == MoveFlag::DOUBLE_PAWN_PUSH);

    static_assert(!Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH).is_quiet());
    static_assert(!Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH).is_capture());
    static_assert(Move(Square::E5, Square::D6, MoveFlag::EN_PASSANT).is_capture());
    static_assert(Move(Square::E5, Square::D6, MoveFlag::EN_PASSANT).is_en_passant());
    static_assert(Move(Square::E5, Square::D6, MoveFlag::EN_PASSANT).en_passant_square() == Square::D5);
    static_assert(Move(Square::E5, Square::F6, MoveFlag::EN_PASSANT).en_passant_square() == Square::F5);
    static_assert(Move(Square::D4, Square::C3, MoveFlag::EN_PASSANT).en_passant_square() == Square::C4);
    static_assert(Move(Square::D4, Square::E3, MoveFlag::EN_PASSANT).en_passant_square() == Square::E4);
    static_assert(Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH).en_passant_square() == Square::INVALID);

    static_assert(Move(Square::E1, Square::G1, MoveFlag::KING_SIDE_CASTLE).is_king_side_castle());
    static_assert(!Move(Square::E1, Square::G1, MoveFlag::KING_SIDE_CASTLE).is_queen_side_castle());
    static_assert(Move(Square::E1, Square::C1, MoveFlag::QUEEN_SIDE_CASTLE).is_queen_side_castle());
    static_assert(!Move(Square::E1, Square::C1, MoveFlag::QUEEN_SIDE_CASTLE).is_king_side_castle());
    static_assert(Move(Square::E1, Square::G1, MoveFlag::KING_SIDE_CASTLE).is_castle());
    static_assert(Move(Square::E1, Square::C1, MoveFlag::QUEEN_SIDE_CASTLE).is_castle());

    static_assert(Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH).is_double_pawn_push());
    static_assert(!Move(Square::E2, Square::E3).is_double_pawn_push());

    static_assert(Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH).double_pawn_single_square() == Square::E3);
    static_assert(Move(Square::E2, Square::E3).double_pawn_single_square() == Square::INVALID);

    static_assert(Move(Square::E7, Square::E8, MoveFlag::KNIGHT_PROMOTE).is_promotion());
    static_assert(Move(Square::E7, Square::E8, MoveFlag::BISHOP_PROMOTE).is_promotion());
    static_assert(Move(Square::E7, Square::E8, MoveFlag::ROOK_PROMOTE).is_promotion());
    static_assert(Move(Square::E7, Square::E8, MoveFlag::QUEEN_PROMOTE).is_promotion());
    static_assert(!Move(Square::E7, Square::E8).is_promotion());
    static_assert(Move(Square::E7, Square::F8, MoveFlag::KNIGHT_PROMOTE_CAPTURE).is_promotion());
    static_assert(Move(Square::E7, Square::F8, MoveFlag::BISHOP_PROMOTE_CAPTURE).is_promotion());
    static_assert(Move(Square::E7, Square::F8, MoveFlag::ROOK_PROMOTE_CAPTURE).is_promotion());
    static_assert(Move(Square::E7, Square::F8, MoveFlag::QUEEN_PROMOTE_CAPTURE).is_promotion());
    static_assert(Move(Square::E7, Square::F8, MoveFlag::KNIGHT_PROMOTE_CAPTURE).is_capture());
    static_assert(Move(Square::E7, Square::F8, MoveFlag::BISHOP_PROMOTE_CAPTURE).is_capture());
    static_assert(Move(Square::E7, Square::F8, MoveFlag::ROOK_PROMOTE_CAPTURE).is_capture());
    static_assert(Move(Square::E7, Square::F8, MoveFlag::QUEEN_PROMOTE_CAPTURE).is_capture());

    static_assert(Move(Square::E7, Square::E8, MoveFlag::KNIGHT_PROMOTE).promote_piece_type() == BasicPieceType::KNIGHT);
    static_assert(Move(Square::E7, Square::F8, MoveFlag::KNIGHT_PROMOTE_CAPTURE).promote_piece_type() == BasicPieceType::KNIGHT);
    static_assert(Move(Square::E7, Square::E8, MoveFlag::BISHOP_PROMOTE).promote_piece_type() == BasicPieceType::BISHOP);
    static_assert(Move(Square::E7, Square::F8, MoveFlag::BISHOP_PROMOTE_CAPTURE).promote_piece_type() == BasicPieceType::BISHOP);
    static_assert(Move(Square::E7, Square::E8, MoveFlag::ROOK_PROMOTE).promote_piece_type() == BasicPieceType::ROOK);
    static_assert(Move(Square::E7, Square::F8, MoveFlag::ROOK_PROMOTE_CAPTURE).promote_piece_type() == BasicPieceType::ROOK);
    static_assert(Move(Square::E7, Square::E8, MoveFlag::QUEEN_PROMOTE).promote_piece_type() == BasicPieceType::QUEEN);
    static_assert(Move(Square::E7, Square::F8, MoveFlag::QUEEN_PROMOTE_CAPTURE).promote_piece_type() == BasicPieceType::QUEEN);

    static_assert(Move(Square::E2, Square::E4) == Move(Square::E2, Square::E4));
    static_assert(Move(Square::E2, Square::E4) != Move(Square::E2, Square::E3));
    static_assert(Move(Square::E2, Square::E4) != Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH));

    return true;
}