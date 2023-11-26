/**
 * @author Steven Goldade
 * @date 11/11/2023
 */
#include <chess/piece.h>

using namespace chess;

auto constexpr piece_type() -> bool {
    static_assert(PieceType(0) == PieceType::NONE, "explicit PieceType(0) == NONE");
    static_assert(PieceType(12) == PieceType::BLACK_KING, "explicit PieceType(12) == BLACK_KING");
    
    static_assert(PieceType(PieceType::NONE) == PieceType::NONE, "explicit PieceType(NONE) == NONE");
    static_assert(PieceType(BasicPieceType::NONE, false) == PieceType::NONE, "PieceType(NONE, false) == NONE");
    static_assert(PieceType(BasicPieceType::NONE, true) == PieceType::NONE, "PieceType(NONE, true) == NONE");
    static_assert(PieceType(BasicPieceType::PAWN, false) == PieceType::WHITE_PAWN, "PieceType(PAWN, false) == WHITE_PAWN");
    static_assert(PieceType(BasicPieceType::KING, true) == PieceType::BLACK_KING, "PieceType(KING, true) == BLACK_KING");

    static_assert(PieceType(BasicPieceType::PAWN, Side::NONE) == PieceType::NONE, "PieceType(PAWN, NONE) == NONE");
    static_assert(PieceType(BasicPieceType::KING, Side::NONE) == PieceType::NONE, "PieceType(KING, NONE) == NONE");
    static_assert(PieceType(BasicPieceType::NONE, Side::WHITE) == PieceType::NONE, "PieceType(NONE, WHITE) == NONE");
    static_assert(PieceType(BasicPieceType::NONE, Side::BLACK) == PieceType::NONE, "PieceType(NONE, BLACK) == NONE");
    static_assert(PieceType(BasicPieceType::PAWN, Side::WHITE) == PieceType::WHITE_PAWN, "PieceType(PAWN, WHITE) == WHITE_PAWN");
    static_assert(PieceType(BasicPieceType::KING, Side::BLACK) == PieceType::BLACK_KING, "PieceType(KING, BLACK) == BLACK_KING");
    
    static_assert(PieceType(PieceType::NONE).side() == Side::NONE, "NONE.side == NONE");
    static_assert(PieceType(PieceType::NONE).opposing_side() == Side::NONE, "NONE.opposing_side == NONE");
    static_assert(!PieceType(PieceType::NONE).is_white(), "!NONE.is_white");
    static_assert(!PieceType(PieceType::NONE).is_black(), "!NONE.is_black");
    static_assert(PieceType(PieceType::NONE).is_none(), "NONE.is_none");
    static_assert(PieceType(PieceType::WHITE_PAWN).side() == Side::WHITE, "WHITE_PAWN.side == WHITE");
    static_assert(PieceType(PieceType::WHITE_PAWN).opposing_side() == Side::BLACK, "WHITE_PAWN.opposing_side == BLACK");
    static_assert(PieceType(PieceType::WHITE_PAWN).is_white(), "WHITE_PAWN.is_white");
    static_assert(!PieceType(PieceType::WHITE_PAWN).is_black(), "!WHITE_PAWN.is_black");
    static_assert(!PieceType(PieceType::WHITE_PAWN).is_none(), "!WHITE_PAWN.is_none");
    static_assert(PieceType(PieceType::WHITE_KING).side() == Side::WHITE, "WHITE_KING.side == WHITE");
    static_assert(PieceType(PieceType::WHITE_KING).opposing_side() == Side::BLACK, "WHITE_KING.opposing_side == BLACK");
    static_assert(PieceType(PieceType::BLACK_PAWN).side() == Side::BLACK, "BLACK_PAWN.side == BLACK");
    static_assert(PieceType(PieceType::BLACK_PAWN).opposing_side() == Side::WHITE, "BLACK_PAWN.opposing_side == WHITE");
    static_assert(!PieceType(PieceType::BLACK_PAWN).is_white(), "!BLACK_PAWN.is_white");
    static_assert(PieceType(PieceType::BLACK_PAWN).is_black(), "BLACK_PAWN.is_black");
    static_assert(!PieceType(PieceType::BLACK_PAWN).is_none(), "!BLACK_PAWN.is_none");
    static_assert(PieceType(PieceType::BLACK_KING).side() == Side::BLACK, "BLACK_KING.side == BLACK");
    static_assert(PieceType(PieceType::BLACK_KING).opposing_side() == Side::WHITE, "BLACK_KING.opposing_side == WHITE");
    
    static_assert(PieceType(PieceType::NONE).basic_piece_type() == BasicPieceType::NONE, "NONE.basic_piece_type = NONE");
    static_assert(PieceType(PieceType::WHITE_PAWN).basic_piece_type() == BasicPieceType::PAWN, "WHITE_PAWN.basic_piece_type = PAWN");
    static_assert(PieceType(PieceType::WHITE_KING).basic_piece_type() == BasicPieceType::KING, "WHITE_KING.basic_piece_type = KING");
    static_assert(PieceType(PieceType::BLACK_PAWN).basic_piece_type() == BasicPieceType::PAWN, "BLACK_PAWN.basic_piece_type = PAWN");
    static_assert(PieceType(PieceType::BLACK_KING).basic_piece_type() == BasicPieceType::KING, "BLACK_KING.basic_piece_type = KING");

    static_assert(PieceType(PieceType::BLACK_KNIGHT).is_opposing_type(Side::WHITE, BasicPieceType::KNIGHT));
    static_assert(PieceType(PieceType::BLACK_KNIGHT).opposes(Side::WHITE));
    static_assert(PieceType(PieceType::BLACK_KNIGHT).opposes(PieceType::WHITE_KING));

    static_assert(PieceType(PieceType::WHITE_PAWN).is_pawn());
    static_assert(PieceType(PieceType::WHITE_KNIGHT).is_knight());
    static_assert(PieceType(PieceType::WHITE_BISHOP).is_bishop());
    static_assert(PieceType(PieceType::WHITE_ROOK).is_rook());
    static_assert(PieceType(PieceType::WHITE_QUEEN).is_queen());
    static_assert(PieceType(PieceType::WHITE_KING).is_king());
    return true;
}

auto constexpr piece() -> bool {
    static_assert(Piece(PieceType::WHITE_PAWN, Square::E2).piece_type() == PieceType::WHITE_PAWN, "Piece(WHITE_PAWN, E2).piece_type = WHITE_PAWN");
    static_assert(Piece(PieceType::WHITE_PAWN, Square::E2).square() == Square::E2, "Piece(WHITE_PAWN, E2).square = E2");
    static_assert(Piece(PieceType::WHITE_PAWN, Square::E2).side() == Side::WHITE, "Piece(WHITE_PAWN, E2).side = WHITE");
    static_assert(Piece(PieceType::BLACK_PAWN, Square::E7).piece_type() == PieceType::BLACK_PAWN, "Piece(BLACK_PAWN, E7).piece_type = BLACK_PAWN");
    static_assert(Piece(PieceType::BLACK_PAWN, Square::E7).square() == Square::E7, "Piece(BLACK_PAWN, E7).square = E7");
    static_assert(Piece(PieceType::BLACK_PAWN, Square::E7).side() == Side::BLACK, "Piece(BLACK_PAWN, E7).side = BLACK");
    static_assert(Piece(PieceType::BLACK_PAWN, Square::E7).opposing_side() == Side::WHITE, "Piece(BLACK_PAWN, E7).opposing_side = WHITE");

    auto queen = Piece(PieceType::WHITE_PAWN, Square::E8);
    queen.promote(BasicPieceType::QUEEN);
    if(queen.piece_type() != PieceType::WHITE_QUEEN) return false;
    queen.demote();
    if(queen.piece_type() != PieceType::WHITE_PAWN) return false;

    static_assert(Piece(PieceType::WHITE_PAWN, Square::E2) == Piece(PieceType::WHITE_PAWN, Square::E2));
    static_assert(Piece(PieceType::WHITE_PAWN, Square::E2) != Piece(PieceType::WHITE_PAWN, Square::E3));
    static_assert(Piece(PieceType::WHITE_PAWN, Square::E2) != Piece(PieceType::BLACK_PAWN, Square::E2));

    return true;
}

auto constexpr test_piece() -> bool {
    static_assert(piece_type(), "Piece Type");
    static_assert(piece(), "Piece");
    return true;
}
