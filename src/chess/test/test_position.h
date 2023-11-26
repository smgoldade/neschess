/**
* @author Steven Goldade
* @date 11/12/2023
*/
#include <chess/position.h>

using namespace chess;

auto constexpr test_pos_construct() noexcept -> bool {
    auto constexpr position = Position();
    auto constexpr fen_position = Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    static_assert(position == fen_position);

    auto constexpr fen_position_2 = Position("rnb1kbnr/ppp1p1pp/3q4/3pPp2/8/5N2/PPPP1PPP/RNBQKB1R w KQkq f6 0 4");
    auto constexpr board = fen_position_2.get_board();
    static_assert(board.piece_at(Square::A8).piece_type() == PieceType::BLACK_ROOK);
    static_assert(board.piece_at(Square::B8).piece_type() == PieceType::BLACK_KNIGHT);
    static_assert(board.piece_at(Square::C8).piece_type() == PieceType::BLACK_BISHOP);
    static_assert(board.piece_at(Square::D8).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::E8).piece_type() == PieceType::BLACK_KING);
    static_assert(board.piece_at(Square::F8).piece_type() == PieceType::BLACK_BISHOP);
    static_assert(board.piece_at(Square::G8).piece_type() == PieceType::BLACK_KNIGHT);
    static_assert(board.piece_at(Square::H8).piece_type() == PieceType::BLACK_ROOK);
    static_assert(board.piece_at(Square::A7).piece_type() == PieceType::BLACK_PAWN);
    static_assert(board.piece_at(Square::B7).piece_type() == PieceType::BLACK_PAWN);
    static_assert(board.piece_at(Square::C7).piece_type() == PieceType::BLACK_PAWN);
    static_assert(board.piece_at(Square::D7).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::E7).piece_type() == PieceType::BLACK_PAWN);
    static_assert(board.piece_at(Square::F7).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::G7).piece_type() == PieceType::BLACK_PAWN);
    static_assert(board.piece_at(Square::H7).piece_type() == PieceType::BLACK_PAWN);
    static_assert(board.piece_at(Square::A6).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::B6).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::C6).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::D6).piece_type() == PieceType::BLACK_QUEEN);
    static_assert(board.piece_at(Square::E6).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::F6).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::G6).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::H6).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::A5).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::B5).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::C5).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::D5).piece_type() == PieceType::BLACK_PAWN);
    static_assert(board.piece_at(Square::E5).piece_type() == PieceType::WHITE_PAWN);
    static_assert(board.piece_at(Square::F5).piece_type() == PieceType::BLACK_PAWN);
    static_assert(board.piece_at(Square::G5).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::H5).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::A4).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::B4).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::C4).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::D4).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::E4).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::F4).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::G4).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::H4).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::A3).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::B3).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::C3).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::D3).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::E3).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::F3).piece_type() == PieceType::WHITE_KNIGHT);
    static_assert(board.piece_at(Square::G3).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::H3).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::A2).piece_type() == PieceType::WHITE_PAWN);
    static_assert(board.piece_at(Square::B2).piece_type() == PieceType::WHITE_PAWN);
    static_assert(board.piece_at(Square::C2).piece_type() == PieceType::WHITE_PAWN);
    static_assert(board.piece_at(Square::D2).piece_type() == PieceType::WHITE_PAWN);
    static_assert(board.piece_at(Square::E2).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::F2).piece_type() == PieceType::WHITE_PAWN);
    static_assert(board.piece_at(Square::G2).piece_type() == PieceType::WHITE_PAWN);
    static_assert(board.piece_at(Square::H2).piece_type() == PieceType::WHITE_PAWN);
    static_assert(board.piece_at(Square::A1).piece_type() == PieceType::WHITE_ROOK);
    static_assert(board.piece_at(Square::B1).piece_type() == PieceType::WHITE_KNIGHT);
    static_assert(board.piece_at(Square::C1).piece_type() == PieceType::WHITE_BISHOP);
    static_assert(board.piece_at(Square::D1).piece_type() == PieceType::WHITE_QUEEN);
    static_assert(board.piece_at(Square::E1).piece_type() == PieceType::WHITE_KING);
    static_assert(board.piece_at(Square::F1).piece_type() == PieceType::WHITE_BISHOP);
    static_assert(board.piece_at(Square::G1).piece_type() == PieceType::NONE);
    static_assert(board.piece_at(Square::H1).piece_type() == PieceType::WHITE_ROOK);
    static_assert(fen_position_2.get_reversible_ply_count() == 0);
    static_assert(fen_position_2.is_white_to_move());
    static_assert(fen_position_2.can_white_king_side_castle());
    static_assert(fen_position_2.can_white_queen_side_castle());
    static_assert(fen_position_2.can_black_king_side_castle());
    static_assert(fen_position_2.can_black_queen_side_castle());
    static_assert(fen_position_2.get_en_passant_square() == Square::F6);
    static_assert(fen_position_2.get_board().get_king_square(Side::WHITE) == Square::E1);
    static_assert(fen_position_2.get_board().get_king_square(Side::BLACK) == Square::E8);
    return true;
}

auto constexpr test_pos_equality() noexcept -> bool {
    auto constexpr position_a = Position();
    auto constexpr position_b = Position();

    static_assert(position_a == position_b);

    return true;
}

auto constexpr test_pos_scandinavian() noexcept -> bool {
    auto position = Position();

    auto e2e4 = Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(e2e4);
    if(position.get_reversible_ply_count() != 0) return false;

    auto d7d5 = Move(Square::D7, Square::D5, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(d7d5);
    if(position.get_reversible_ply_count() != 0) return false;

    auto exd5 = Move(Square::E4, Square::D5, MoveFlag::CAPTURE);
    position.make_move(exd5);
    if(position.get_reversible_ply_count() != 0) return false;

    auto Qxd5 = Move(Square::D8, Square::D5, MoveFlag::CAPTURE);
    position.make_move(Qxd5);
    if(position.get_reversible_ply_count() != 0) return false;

    auto Kc3 = Move(Square::B1, Square::C3);
    position.make_move(Kc3);
    if(position.get_reversible_ply_count() != 1) return false;

    auto Qa5 = Move(Square::D5, Square::A5);
    position.make_move(Qa5);
    if(position.get_reversible_ply_count() != 2) return false;


    position.unmake_move(Qa5);
    if(position.get_reversible_ply_count() != 1) return false;
    position.unmake_move(Kc3);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(Qxd5);
    position.unmake_move(exd5);
    position.unmake_move(d7d5);
    position.unmake_move(e2e4);

    auto constexpr new_position = Position();
    return position == new_position;
}

auto constexpr test_pos_king_side_castle() noexcept -> bool {
    auto position = Position();

    auto e2e4 = Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(e2e4);
    if(position.get_reversible_ply_count() != 0) return false;

    auto e7e5 = Move(Square::E7, Square::E5, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(e7e5);
    if(position.get_reversible_ply_count() != 0) return false;

    auto Kf3 = Move(Square::G1, Square::F3);
    position.make_move(Kf3);
    if(position.get_reversible_ply_count() != 1) return false;

    auto Kf6 = Move(Square::G8, Square::F6);
    position.make_move(Kf6);
    if(position.get_reversible_ply_count() != 2) return false;

    auto Bd3 = Move(Square::F1, Square::D3);
    position.make_move(Bd3);
    if(position.get_reversible_ply_count() != 3) return false;

    auto Bd6 = Move(Square::F8, Square::D6);
    position.make_move(Bd6);
    if(position.get_reversible_ply_count() != 4) return false;

    auto WOO = Move(Square::E1, Square::G1, MoveFlag::KING_SIDE_CASTLE);
    position.make_move(WOO);
    if(position.get_reversible_ply_count() != 5) return false;
    if(position.can_white_king_side_castle()) return false;
    if(position.can_white_queen_side_castle()) return false;

    auto BOO = Move(Square::E8, Square::G8, MoveFlag::KING_SIDE_CASTLE);
    position.make_move(BOO);
    if(position.get_reversible_ply_count() != 6) return false;
    if(position.can_black_king_side_castle()) return false;
    if(position.can_black_queen_side_castle()) return false;

    position.unmake_move(BOO);
    if(!position.can_black_king_side_castle()) return false;
    if(!position.can_black_queen_side_castle()) return false;
    if(position.get_reversible_ply_count() != 5) return false;
    position.unmake_move(WOO);
    if(!position.can_white_king_side_castle()) return false;
    if(!position.can_white_queen_side_castle()) return false;
    if(position.get_reversible_ply_count() != 4) return false;
    position.unmake_move(Bd6);
    position.unmake_move(Bd3);
    position.unmake_move(Kf6);
    position.unmake_move(Kf3);
    position.unmake_move(e7e5);
    position.unmake_move(e2e4);

    auto constexpr new_position = Position();
    return position == new_position;
}

auto constexpr test_pos_queen_side_castle() noexcept -> bool {
    auto position = Position();

    auto d2d4 = Move(Square::D2, Square::D4, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(d2d4);
    if(position.get_reversible_ply_count() != 0) return false;

    auto d7d5 = Move(Square::D7, Square::D5, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(d7d5);
    if(position.get_reversible_ply_count() != 0) return false;

    auto Kc3 = Move(Square::B1, Square::C3);
    position.make_move(Kc3);
    if(position.get_reversible_ply_count() != 1) return false;

    auto Kc6 = Move(Square::B8, Square::C6);
    position.make_move(Kc6);
    if(position.get_reversible_ply_count() != 2) return false;

    auto Be3 = Move(Square::C1, Square::E3);
    position.make_move(Be3);
    if(position.get_reversible_ply_count() != 3) return false;

    auto Be6 = Move(Square::C8, Square::E6);
    position.make_move(Be6);
    if(position.get_reversible_ply_count() != 4) return false;

    auto Qd2 = Move(Square::D1, Square::D2);
    position.make_move(Qd2);
    if(position.get_reversible_ply_count() != 5) return false;

    auto Qd7 = Move(Square::D8, Square::D7);
    position.make_move(Qd7);
    if(position.get_reversible_ply_count() != 6) return false;

    auto WOOO = Move(Square::E1, Square::C1, MoveFlag::QUEEN_SIDE_CASTLE);
    position.make_move(WOOO);
    if(position.can_white_king_side_castle()) return false;
    if(position.can_white_queen_side_castle()) return false;
    if(position.get_reversible_ply_count() != 7) return false;

    auto BOOO = Move(Square::E8, Square::C8, MoveFlag::QUEEN_SIDE_CASTLE);
    position.make_move(BOOO);
    if(position.can_black_king_side_castle()) return false;
    if(position.can_black_queen_side_castle()) return false;
    if(position.get_reversible_ply_count() != 8) return false;

    position.unmake_move(BOOO);
    if(!position.can_black_king_side_castle()) return false;
    if(!position.can_black_queen_side_castle()) return false;
    if(position.get_reversible_ply_count() != 7) return false;
    position.unmake_move(WOOO);
    if(!position.can_black_king_side_castle()) return false;
    if(!position.can_black_queen_side_castle()) return false;
    if(position.get_reversible_ply_count() != 6) return false;
    position.unmake_move(Qd7);
    position.unmake_move(Qd2);
    position.unmake_move(Be6);
    position.unmake_move(Be3);
    position.unmake_move(Kc6);
    position.unmake_move(Kc3);
    position.unmake_move(d7d5);
    position.unmake_move(d2d4);

    auto constexpr new_position = Position();
    return position == new_position;
}

auto constexpr test_pos_en_passant() noexcept -> bool {
    auto position = Position();

    auto e2e4 = Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(e2e4);
    if(position.get_reversible_ply_count() != 0) return false;

    auto b7b5 = Move(Square::B7, Square::B5, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(b7b5);
    if(position.get_reversible_ply_count() != 0) return false;

    auto e4e5 = Move(Square::E4, Square::E5);
    position.make_move(e4e5);
    if(position.get_reversible_ply_count() != 0) return false;

    auto b5b4 = Move(Square::B5, Square::B4);
    position.make_move(b5b4);
    if(position.get_reversible_ply_count() != 0) return false;

    auto a2a4 = Move(Square::A2, Square::A4, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(a2a4);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::A3) return false;

    auto bxa3 = Move(Square::B4, Square::A3, MoveFlag::EN_PASSANT);
    position.make_move(bxa3);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;

    position.unmake_move(bxa3);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::A3) return false;

    position.unmake_move(a2a4);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;

    auto c2c4 = Move(Square::C2, Square::C4, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(c2c4);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::C3) return false;

    auto bxc3 = Move(Square::B4, Square::C3, MoveFlag::EN_PASSANT);
    position.make_move(bxc3);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;

    position.unmake_move(bxc3);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::C3) return false;

    position.unmake_move(c2c4);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;

    auto d2d3 = Move(Square::D2, Square::D3);
    position.make_move(d2d3);
    if(position.get_reversible_ply_count() != 0) return false;

    auto d7d5 = Move(Square::D7, Square::D5, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(d7d5);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::D6) return false;

    auto exd6 = Move(Square::E5, Square::D6, MoveFlag::EN_PASSANT);
    position.make_move(exd6);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;

    position.unmake_move(exd6);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::D6) return false;
    position.unmake_move(d7d5);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;

    auto f7f5 = Move(Square::F7, Square::F5, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(f7f5);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::F6) return false;

    auto exf6 = Move(Square::E5, Square::F6, MoveFlag::EN_PASSANT);
    position.make_move(exf6);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;

    position.unmake_move(exf6);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::F6) return false;
    position.unmake_move(f7f5);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;

    position.unmake_move(d2d3);
    position.unmake_move(b5b4);
    position.unmake_move(e4e5);
    position.unmake_move(b7b5);
    position.unmake_move(e2e4);

    auto constexpr new_position = Position();
    return position == new_position;
}

auto constexpr test_pos_promotion() noexcept -> bool {
    auto position = Position();

    auto b2b4 = Move(Square::B2, Square::B4, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(b2b4);
    if(position.get_reversible_ply_count() != 0) return false;

    auto a7a5 = Move(Square::A7, Square::A5, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(a7a5);
    if(position.get_reversible_ply_count() != 0) return false;

    auto bxa5 = Move(Square::B4, Square::A5, MoveFlag::CAPTURE);
    position.make_move(bxa5);
    if(position.get_reversible_ply_count() != 0) return false;

    auto b7b5 = Move(Square::B7, Square::B5, MoveFlag::DOUBLE_PAWN_PUSH);
    position.make_move(b7b5);
    if(position.get_en_passant_square() != Square::B6) return false;
    if(position.get_reversible_ply_count() != 0) return false;

    auto a5a6 = Move(Square::A5, Square::A6);
    position.make_move(a5a6);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;
    if(!position.can_black_queen_side_castle()) return false;

    auto Ra7 = Move(Square::A8, Square::A7);
    position.make_move(Ra7);
    if(position.get_reversible_ply_count() != 1) return false;
    if(position.can_black_queen_side_castle()) return false;

    auto Kc3 = Move(Square::B1, Square::C3);
    position.make_move(Kc3);
    if(position.get_reversible_ply_count() != 2) return false;

    auto Rb7 = Move(Square::A7, Square::B7);
    position.make_move(Rb7);
    if(position.get_reversible_ply_count() != 3) return false;

    auto a6a7 = Move(Square::A6, Square::A7);
    position.make_move(a6a7);
    if(position.get_reversible_ply_count() != 0) return false;

    auto b5b4 = Move(Square::B5, Square::B4);
    position.make_move(b5b4);
    if(position.get_reversible_ply_count() != 0) return false;

    auto a8Q = Move(Square::A7, Square::A8, MoveFlag::QUEEN_PROMOTE);
    position.make_move(a8Q);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(a8Q);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.can_black_queen_side_castle()) return false;

    auto a8R = Move(Square::A7, Square::A8, MoveFlag::ROOK_PROMOTE);
    position.make_move(a8R);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(a8R);
    if(position.get_reversible_ply_count() != 0) return false;

    auto a8B = Move(Square::A7, Square::A8, MoveFlag::BISHOP_PROMOTE);
    position.make_move(a8B);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(a8B);
    if(position.get_reversible_ply_count() != 0) return false;

    auto a8K = Move(Square::A7, Square::A8, MoveFlag::KNIGHT_PROMOTE);
    position.make_move(a8K);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(a8K);
    if(position.get_reversible_ply_count() != 0) return false;

    auto axb8Q = Move(Square::A7, Square::B8, MoveFlag::QUEEN_PROMOTE_CAPTURE);
    position.make_move(axb8Q);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(axb8Q);
    if(position.get_reversible_ply_count() != 0) return false;

    auto axb8R = Move(Square::A7, Square::B8, MoveFlag::ROOK_PROMOTE_CAPTURE);
    position.make_move(axb8R);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(axb8R);
    if(position.get_reversible_ply_count() != 0) return false;

    auto axb8B = Move(Square::A7, Square::B8, MoveFlag::BISHOP_PROMOTE_CAPTURE);
    position.make_move(axb8B);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(axb8B);
    if(position.get_reversible_ply_count() != 0) return false;

    auto axb8K = Move(Square::A7, Square::B8, MoveFlag::KNIGHT_PROMOTE_CAPTURE);
    position.make_move(axb8K);
    if(position.get_reversible_ply_count() != 0) return false;

    auto b4b3 = Move(Square::B4, Square::B3);
    position.make_move(b4b3);
    if(position.get_reversible_ply_count() != 0) return false;

    auto Ka6 = Move(Square::B8, Square::A6);
    position.make_move(Ka6);
    if(position.get_reversible_ply_count() != 1) return false;

    auto b3b2 = Move(Square::B3, Square::B2);
    position.make_move(b3b2);
    if(position.get_reversible_ply_count() != 0) return false;

    auto Kb8 = Move(Square::A6, Square::B8);
    position.make_move(Kb8);
    if(position.get_reversible_ply_count() != 1) return false;

    auto b1Q = Move(Square::B2, Square::B1, MoveFlag::QUEEN_PROMOTE);
    position.make_move(b1Q);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(b1Q);
    if(position.get_reversible_ply_count() != 1) return false;

    auto b1R = Move(Square::B2, Square::B1, MoveFlag::ROOK_PROMOTE);
    position.make_move(b1R);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(b1R);
    if(position.get_reversible_ply_count() != 1) return false;

    auto b1B = Move(Square::B2, Square::B1, MoveFlag::BISHOP_PROMOTE);
    position.make_move(b1B);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(b1B);
    if(position.get_reversible_ply_count() != 1) return false;

    auto b1K = Move(Square::B2, Square::B1, MoveFlag::KNIGHT_PROMOTE);
    position.make_move(b1K);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(b1K);
    if(position.get_reversible_ply_count() != 1) return false;

    auto bxa1Q = Move(Square::B2, Square::A1, MoveFlag::QUEEN_PROMOTE_CAPTURE);
    position.make_move(bxa1Q);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(bxa1Q);
    if(position.get_reversible_ply_count() != 1) return false;

    auto bxa1R = Move(Square::B2, Square::A1, MoveFlag::ROOK_PROMOTE_CAPTURE);
    position.make_move(bxa1R);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(bxa1R);
    if(position.get_reversible_ply_count() != 1) return false;

    auto bxa1B = Move(Square::B2, Square::A1, MoveFlag::BISHOP_PROMOTE_CAPTURE);
    position.make_move(bxa1B);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(bxa1B);
    if(position.get_reversible_ply_count() != 1) return false;

    auto bxa1K = Move(Square::B2, Square::A1, MoveFlag::KNIGHT_PROMOTE_CAPTURE);
    position.make_move(bxa1K);
    if(position.get_reversible_ply_count() != 0) return false;

    position.unmake_move(bxa1K);
    if(position.get_reversible_ply_count() != 1) return false;
    position.unmake_move(Kb8);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(b3b2);
    if(position.get_reversible_ply_count() != 1) return false;
    position.unmake_move(Ka6);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(b4b3);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(axb8K);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(b5b4);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(a6a7);
    if(position.get_reversible_ply_count() != 3) return false;
    position.unmake_move(Rb7);
    if(position.get_reversible_ply_count() != 2) return false;
    position.unmake_move(Kc3);
    if(position.get_reversible_ply_count() != 1) return false;
    position.unmake_move(Ra7);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;
    position.unmake_move(a5a6);
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::B6) return false;
    position.unmake_move(b7b5);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(bxa5);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(a7a5);
    if(position.get_reversible_ply_count() != 0) return false;
    position.unmake_move(b2b4);


    if(!position.is_white_to_move()) return false;
    if(!position.can_white_king_side_castle()) return false;
    if(!position.can_white_queen_side_castle()) return false;
    if(!position.can_black_king_side_castle()) return false;
    if(!position.can_black_queen_side_castle()) return false;
    if(position.get_reversible_ply_count() != 0) return false;
    if(position.get_en_passant_square() != Square::INVALID) return false;

    auto constexpr new_position = Position();
    return position == new_position;
}

auto constexpr test_pos_make_unmake() noexcept -> bool {
    static_assert(test_pos_scandinavian(), "Scandinavian Make Move");
    static_assert(test_pos_king_side_castle(), "King Side Castle Make Move");
    static_assert(test_pos_queen_side_castle(), "Queen Side Castle Make Move");
    static_assert(test_pos_en_passant(), "En Passant Make Move");
    static_assert(test_pos_promotion(), "Promotion");

    return true;
}

auto constexpr test_position() noexcept -> bool {
    static_assert(test_pos_equality(), "Equality");
    static_assert(test_pos_construct(), "Construct");
    static_assert(test_pos_make_unmake(), "Make/Unmake Move");
    return true;
}