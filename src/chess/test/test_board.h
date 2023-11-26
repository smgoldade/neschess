/**
* @author Steven Goldade
* @date 11/12/2023
*/
#include <chess/board.h>

using namespace chess;

//TODO: PIECES CHECKS
auto constexpr test_construct() noexcept -> bool {
    auto board = Board();

    if(board.piece_at(Square::A1).piece_type() != PieceType::WHITE_ROOK) return false;
    if(board.piece_at(Square::B1).piece_type() != PieceType::WHITE_KNIGHT) return false;
    if(board.piece_at(Square::C1).piece_type() != PieceType::WHITE_BISHOP) return false;
    if(board.piece_at(Square::D1).piece_type() != PieceType::WHITE_QUEEN) return false;
    if(board.piece_at(Square::E1).piece_type() != PieceType::WHITE_KING) return false;
    if(board.piece_at(Square::F1).piece_type() != PieceType::WHITE_BISHOP) return false;
    if(board.piece_at(Square::G1).piece_type() != PieceType::WHITE_KNIGHT) return false;
    if(board.piece_at(Square::H1).piece_type() != PieceType::WHITE_ROOK) return false;
    if(board.piece_at(Square::A2).piece_type() != PieceType::WHITE_PAWN) return false;
    if(board.piece_at(Square::B2).piece_type() != PieceType::WHITE_PAWN) return false;
    if(board.piece_at(Square::C2).piece_type() != PieceType::WHITE_PAWN) return false;
    if(board.piece_at(Square::D2).piece_type() != PieceType::WHITE_PAWN) return false;
    if(board.piece_at(Square::E2).piece_type() != PieceType::WHITE_PAWN) return false;
    if(board.piece_at(Square::F2).piece_type() != PieceType::WHITE_PAWN) return false;
    if(board.piece_at(Square::G2).piece_type() != PieceType::WHITE_PAWN) return false;
    if(board.piece_at(Square::H2).piece_type() != PieceType::WHITE_PAWN) return false;

    if(!board.no_piece_at(Square::A3)) return false;
    if(!board.no_piece_at(Square::B3)) return false;
    if(!board.no_piece_at(Square::C3)) return false;
    if(!board.no_piece_at(Square::D3)) return false;
    if(!board.no_piece_at(Square::E3)) return false;
    if(!board.no_piece_at(Square::F3)) return false;
    if(!board.no_piece_at(Square::G3)) return false;
    if(!board.no_piece_at(Square::H3)) return false;
    if(!board.no_piece_at(Square::A4)) return false;
    if(!board.no_piece_at(Square::B4)) return false;
    if(!board.no_piece_at(Square::C4)) return false;
    if(!board.no_piece_at(Square::D4)) return false;
    if(!board.no_piece_at(Square::E4)) return false;
    if(!board.no_piece_at(Square::F4)) return false;
    if(!board.no_piece_at(Square::G4)) return false;
    if(!board.no_piece_at(Square::H4)) return false;
    if(!board.no_piece_at(Square::A5)) return false;
    if(!board.no_piece_at(Square::B5)) return false;
    if(!board.no_piece_at(Square::C5)) return false;
    if(!board.no_piece_at(Square::D5)) return false;
    if(!board.no_piece_at(Square::E5)) return false;
    if(!board.no_piece_at(Square::F5)) return false;
    if(!board.no_piece_at(Square::G5)) return false;
    if(!board.no_piece_at(Square::H5)) return false;
    if(!board.no_piece_at(Square::A6)) return false;
    if(!board.no_piece_at(Square::B6)) return false;
    if(!board.no_piece_at(Square::C6)) return false;
    if(!board.no_piece_at(Square::D6)) return false;
    if(!board.no_piece_at(Square::E6)) return false;
    if(!board.no_piece_at(Square::F6)) return false;
    if(!board.no_piece_at(Square::G6)) return false;
    if(!board.no_piece_at(Square::H6)) return false;

    if(board.piece_at(Square::A7).piece_type() != PieceType::BLACK_PAWN) return false;
    if(board.piece_at(Square::B7).piece_type() != PieceType::BLACK_PAWN) return false;
    if(board.piece_at(Square::C7).piece_type() != PieceType::BLACK_PAWN) return false;
    if(board.piece_at(Square::D7).piece_type() != PieceType::BLACK_PAWN) return false;
    if(board.piece_at(Square::E7).piece_type() != PieceType::BLACK_PAWN) return false;
    if(board.piece_at(Square::F7).piece_type() != PieceType::BLACK_PAWN) return false;
    if(board.piece_at(Square::G7).piece_type() != PieceType::BLACK_PAWN) return false;
    if(board.piece_at(Square::H7).piece_type() != PieceType::BLACK_PAWN) return false;
    if(board.piece_at(Square::A8).piece_type() != PieceType::BLACK_ROOK) return false;
    if(board.piece_at(Square::B8).piece_type() != PieceType::BLACK_KNIGHT) return false;
    if(board.piece_at(Square::C8).piece_type() != PieceType::BLACK_BISHOP) return false;
    if(board.piece_at(Square::D8).piece_type() != PieceType::BLACK_QUEEN) return false;
    if(board.piece_at(Square::E8).piece_type() != PieceType::BLACK_KING) return false;
    if(board.piece_at(Square::F8).piece_type() != PieceType::BLACK_BISHOP) return false;
    if(board.piece_at(Square::G8).piece_type() != PieceType::BLACK_KNIGHT) return false;
    if(board.piece_at(Square::H8).piece_type() != PieceType::BLACK_ROOK) return false;

    return true;
}

auto constexpr test_board_equality() noexcept -> bool {
    auto constexpr board_a = Board();
    auto constexpr board_b = Board();

    static_assert(board_a == board_b);

    return true;
}

auto constexpr test_basics_of_move(Board& board, const Move& move) noexcept -> bool {
    auto const from_square = move.from_square();
    auto const to_square = move.to_square();

    auto from_piece = board.piece_at(from_square);
    auto const to_piece = board.piece_at(to_square);

    if(move.is_promotion()) from_piece.promote(move.promote_piece_type());

    board.make_move(move);
    if(!board.no_piece_at(from_square)) return false;
    if(board.piece_at(to_square).piece_type() != from_piece.piece_type()) return false;

    board.unmake_move(move);
    if(move.is_promotion()) from_piece.demote();
    if(board.piece_at(from_square) != from_piece) return false;
    if(board.piece_at(to_square) != to_piece) return false;
    return true;
}

auto constexpr test_scandinavian() noexcept -> bool {
    auto board = Board();

    auto e2e4 = Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, e2e4)) return false;
    board.make_move(e2e4);

    auto d7d5 = Move(Square::D7, Square::D5, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, d7d5)) return false;
    board.make_move(d7d5);

    auto exd5 = Move(Square::E4, Square::D5, MoveFlag::CAPTURE);
    if(!test_basics_of_move(board, exd5)) return false;
    board.make_move(exd5);

    auto Qxd5 = Move(Square::D8, Square::D5, MoveFlag::CAPTURE);
    if(!test_basics_of_move(board, Qxd5)) return false;
    board.make_move(Qxd5);

    auto Kc3 = Move(Square::B1, Square::C3);
    if(!test_basics_of_move(board, Kc3)) return false;
    board.make_move(Kc3);

    auto Qa5 = Move(Square::D5, Square::A5);
    if(!test_basics_of_move(board, Qa5)) return false;
    board.make_move(Qa5);

    board.unmake_move(Qa5);
    board.unmake_move(Kc3);
    board.unmake_move(Qxd5);
    board.unmake_move(exd5);
    board.unmake_move(d7d5);
    board.unmake_move(e2e4);

    auto constexpr new_board = Board();
    return board == new_board;
}

auto constexpr test_king_side_castle() noexcept -> bool {
    auto board = Board();
    auto e2e4 = Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, e2e4)) return false;
    board.make_move(e2e4);

    auto e7e5 = Move(Square::E7, Square::E5, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, e7e5)) return false;
    board.make_move(e7e5);

    auto Kf3 = Move(Square::G1, Square::F3);
    if(!test_basics_of_move(board, Kf3)) return false;
    board.make_move(Kf3);

    auto Kf6 = Move(Square::G8, Square::F6);
    if(!test_basics_of_move(board, Kf6)) return false;
    board.make_move(Kf6);

    auto Bd3 = Move(Square::F1, Square::D3);
    if(!test_basics_of_move(board, Bd3)) return false;
    board.make_move(Bd3);

    auto Bd6 = Move(Square::F8, Square::D6);
    if(!test_basics_of_move(board, Bd6)) return false;
    board.make_move(Bd6);

    auto WOO = Move(Square::E1, Square::G1, MoveFlag::KING_SIDE_CASTLE);
    if(!test_basics_of_move(board, WOO)) return false;
    if(!board.no_piece_at(Square::F1)) return false;
    if(board.piece_at(Square::H1).piece_type() != PieceType::WHITE_ROOK) return false;
    board.make_move(WOO);
    if(!board.no_piece_at(Square::H1)) return false;
    if(board.piece_at(Square::F1).piece_type() != PieceType::WHITE_ROOK) return false;

    auto BOO = Move(Square::E8, Square::G8, MoveFlag::KING_SIDE_CASTLE);
    if(!test_basics_of_move(board, BOO)) return false;
    if(!board.no_piece_at(Square::F8)) return false;
    if(board.piece_at(Square::H8).piece_type() != PieceType::BLACK_ROOK) return false;
    board.make_move(BOO);
    if(!board.no_piece_at(Square::H8)) return false;
    if(board.piece_at(Square::F8).piece_type() != PieceType::BLACK_ROOK) return false;

    board.unmake_move(BOO);
    board.unmake_move(WOO);
    board.unmake_move(Bd6);
    board.unmake_move(Bd3);
    board.unmake_move(Kf6);
    board.unmake_move(Kf3);
    board.unmake_move(e7e5);
    board.unmake_move(e2e4);

    auto constexpr new_board = Board();
    return board == new_board;
}

auto constexpr test_queen_side_castle() noexcept -> bool {
    auto board = Board();
    auto d2d4 = Move(Square::D2, Square::D4, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, d2d4)) return false;
    board.make_move(d2d4);

    auto d7d5 = Move(Square::D7, Square::D5, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, d7d5)) return false;
    board.make_move(d7d5);

    auto Kc3 = Move(Square::B1, Square::C3);
    if(!test_basics_of_move(board, Kc3)) return false;
    board.make_move(Kc3);

    auto Kc6 = Move(Square::B8, Square::C6);
    if(!test_basics_of_move(board, Kc6)) return false;
    board.make_move(Kc6);

    auto Be3 = Move(Square::C1, Square::E3);
    if(!test_basics_of_move(board, Be3)) return false;
    board.make_move(Be3);

    auto Be6 = Move(Square::C8, Square::E6);
    if(!test_basics_of_move(board, Be6)) return false;
    board.make_move(Be6);

    auto Qd2 = Move(Square::D1, Square::D2);
    if(!test_basics_of_move(board, Qd2)) return false;
    board.make_move(Qd2);

    auto Qd7 = Move(Square::D8, Square::D7);
    if(!test_basics_of_move(board, Qd7)) return false;
    board.make_move(Qd7);

    auto WOOO = Move(Square::E1, Square::C1, MoveFlag::QUEEN_SIDE_CASTLE);
    if(!test_basics_of_move(board, WOOO)) return false;
    if(!board.no_piece_at(Square::B1)) return false;
    if(!board.no_piece_at(Square::D1)) return false;
    if(board.piece_at(Square::A1).piece_type() != PieceType::WHITE_ROOK) return false;
    board.make_move(WOOO);
    if(!board.no_piece_at(Square::A1)) return false;
    if(!board.no_piece_at(Square::B1)) return false;
    if(board.piece_at(Square::D1).piece_type() != PieceType::WHITE_ROOK) return false;

    auto BOOO = Move(Square::E8, Square::C8, MoveFlag::QUEEN_SIDE_CASTLE);
    if(!test_basics_of_move(board, BOOO)) return false;
    if(!board.no_piece_at(Square::B8)) return false;
    if(!board.no_piece_at(Square::D8)) return false;
    if(board.piece_at(Square::A8).piece_type() != PieceType::BLACK_ROOK) return false;
    board.make_move(BOOO);
    if(!board.no_piece_at(Square::A8)) return false;
    if(!board.no_piece_at(Square::B8)) return false;
    if(board.piece_at(Square::D8).piece_type() != PieceType::BLACK_ROOK) return false;

    board.unmake_move(BOOO);
    board.unmake_move(WOOO);
    board.unmake_move(Qd7);
    board.unmake_move(Qd2);
    board.unmake_move(Be6);
    board.unmake_move(Be3);
    board.unmake_move(Kc6);
    board.unmake_move(Kc3);
    board.unmake_move(d7d5);
    board.unmake_move(d2d4);

    auto constexpr new_board = Board();
    return board == new_board;
}

auto constexpr test_en_passant() noexcept -> bool {
    auto board = Board();

    auto e2e4 = Move(Square::E2, Square::E4, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, e2e4)) return false;
    board.make_move(e2e4);

    auto b7b5 = Move(Square::B7, Square::B5, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, b7b5)) return false;
    board.make_move(b7b5);

    auto e4e5 = Move(Square::E4, Square::E5);
    if(!test_basics_of_move(board, e4e5)) return false;
    board.make_move(e4e5);

    auto b5b4 = Move(Square::B5, Square::B4);
    if(!test_basics_of_move(board, b5b4)) return false;
    board.make_move(b5b4);

    auto a2a4 = Move(Square::A2, Square::A4, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, a2a4)) return false;
    board.make_move(a2a4);

    auto bxa3 = Move(Square::B4, Square::A3, MoveFlag::EN_PASSANT);
    if(!test_basics_of_move(board, bxa3)) return false;
    board.make_move(bxa3);
    if(!board.no_piece_at(Square::A4)) return false;
    board.unmake_move(bxa3);
    board.unmake_move(a2a4);

    auto c2c4 = Move(Square::C2, Square::C4, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, c2c4)) return false;
    board.make_move(c2c4);

    auto bxc3 = Move(Square::B4, Square::C3, MoveFlag::EN_PASSANT);
    if(!test_basics_of_move(board, bxc3)) return false;
    board.make_move(bxc3);
    if(!board.no_piece_at(Square::C4)) return false;
    board.unmake_move(bxc3);
    board.unmake_move(c2c4);

    auto d2d3 = Move(Square::D2, Square::D3);
    if(!test_basics_of_move(board, d2d3)) return false;
    board.make_move(d2d3);

    auto d7d5 = Move(Square::D7, Square::D5, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, d7d5)) return false;
    board.make_move(d7d5);

    auto exd6 = Move(Square::E5, Square::D6, MoveFlag::EN_PASSANT);
    if(!test_basics_of_move(board, exd6)) return false;
    board.make_move(exd6);

    board.unmake_move(exd6);
    board.unmake_move(d7d5);

    auto f7f5 = Move(Square::F7, Square::F5, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, f7f5)) return false;
    board.make_move(f7f5);

    auto exf6 = Move(Square::E5, Square::F6, MoveFlag::EN_PASSANT);
    if(!test_basics_of_move(board, exf6)) return false;
    board.make_move(exf6);

    board.unmake_move(exf6);
    board.unmake_move(f7f5);
    board.unmake_move(d2d3);
    board.unmake_move(b5b4);
    board.unmake_move(e4e5);
    board.unmake_move(b7b5);
    board.unmake_move(e2e4);

    auto constexpr new_board = Board();
    return board == new_board;
}

auto constexpr test_promotion() noexcept -> bool {
    auto board = Board();

    auto b2b4 = Move(Square::B2, Square::B4, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, b2b4)) return false;
    board.make_move(b2b4);

    auto a7a5 = Move(Square::A7, Square::A5, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, a7a5)) return false;
    board.make_move(a7a5);

    auto bxa5 = Move(Square::B4, Square::A5, MoveFlag::CAPTURE);
    if(!test_basics_of_move(board, bxa5)) return false;
    board.make_move(bxa5);

    auto b7b5 = Move(Square::B7, Square::B5, MoveFlag::DOUBLE_PAWN_PUSH);
    if(!test_basics_of_move(board, b7b5)) return false;
    board.make_move(b7b5);

    auto a5a6 = Move(Square::A5, Square::A6);
    if(!test_basics_of_move(board, a5a6)) return false;
    board.make_move(a5a6);

    auto Ra7 = Move(Square::A8, Square::A7);
    if(!test_basics_of_move(board, Ra7)) return false;
    board.make_move(Ra7);

    auto Kc3 = Move(Square::B1, Square::C3);
    if(!test_basics_of_move(board, Kc3)) return false;
    board.make_move(Kc3);

    auto Rb7 = Move(Square::A7, Square::B7);
    if(!test_basics_of_move(board, Rb7)) return false;
    board.make_move(Rb7);

    auto a6a7 = Move(Square::A6, Square::A7);
    if(!test_basics_of_move(board, a6a7)) return false;
    board.make_move(a6a7);

    auto b5b4 = Move(Square::B5, Square::B4);
    if(!test_basics_of_move(board, b5b4)) return false;
    board.make_move(b5b4);

    auto a8Q = Move(Square::A7, Square::A8, MoveFlag::QUEEN_PROMOTE);
    if(!test_basics_of_move(board, a8Q)) return false;
    board.make_move(a8Q);
    board.unmake_move(a8Q);

    auto a8R = Move(Square::A7, Square::A8, MoveFlag::ROOK_PROMOTE);
    if(!test_basics_of_move(board, a8R)) return false;
    board.make_move(a8R);
    board.unmake_move(a8R);

    auto a8B = Move(Square::A7, Square::A8, MoveFlag::BISHOP_PROMOTE);
    if(!test_basics_of_move(board, a8B)) return false;
    board.make_move(a8B);
    board.unmake_move(a8B);

    auto a8K = Move(Square::A7, Square::A8, MoveFlag::KNIGHT_PROMOTE);
    if(!test_basics_of_move(board, a8K)) return false;
    board.make_move(a8K);
    board.unmake_move(a8K);

    auto axb8Q = Move(Square::A7, Square::B8, MoveFlag::QUEEN_PROMOTE_CAPTURE);
    if(!test_basics_of_move(board, axb8Q)) return false;
    board.make_move(axb8Q);
    board.unmake_move(axb8Q);

    auto axb8R = Move(Square::A7, Square::B8, MoveFlag::ROOK_PROMOTE_CAPTURE);
    if(!test_basics_of_move(board, axb8R)) return false;
    board.make_move(axb8R);
    board.unmake_move(axb8R);

    auto axb8B = Move(Square::A7, Square::B8, MoveFlag::BISHOP_PROMOTE_CAPTURE);
    if(!test_basics_of_move(board, axb8B)) return false;
    board.make_move(axb8B);
    board.unmake_move(axb8B);

    auto axb8K = Move(Square::A7, Square::B8, MoveFlag::KNIGHT_PROMOTE_CAPTURE);
    if(!test_basics_of_move(board, axb8K)) return false;
    board.make_move(axb8K);

    auto b4b3 = Move(Square::B4, Square::B3);
    if(!test_basics_of_move(board, b4b3)) return false;
    board.make_move(b4b3);

    auto Ka6 = Move(Square::B8, Square::A6);
    if(!test_basics_of_move(board, Ka6)) return false;
    board.make_move(Ka6);

    auto b3b2 = Move(Square::B3, Square::B2);
    if(!test_basics_of_move(board, b3b2)) return false;
    board.make_move(b3b2);

    auto Kb8 = Move(Square::A6, Square::B8);
    if(!test_basics_of_move(board, Kb8)) return false;
    board.make_move(Kb8);

    auto b1Q = Move(Square::B2, Square::B1, MoveFlag::QUEEN_PROMOTE);
    if(!test_basics_of_move(board, b1Q)) return false;
    board.make_move(b1Q);
    board.unmake_move(b1Q);

    auto b1R = Move(Square::B2, Square::B1, MoveFlag::ROOK_PROMOTE);
    if(!test_basics_of_move(board, b1R)) return false;
    board.make_move(b1R);
    board.unmake_move(b1R);

    auto b1B = Move(Square::B2, Square::B1, MoveFlag::BISHOP_PROMOTE);
    if(!test_basics_of_move(board, b1B)) return false;
    board.make_move(b1B);
    board.unmake_move(b1B);

    auto b1K = Move(Square::B2, Square::B1, MoveFlag::KNIGHT_PROMOTE);
    if(!test_basics_of_move(board, b1K)) return false;
    board.make_move(b1K);
    board.unmake_move(b1K);

    auto bxa1Q = Move(Square::B2, Square::A1, MoveFlag::QUEEN_PROMOTE_CAPTURE);
    if(!test_basics_of_move(board, bxa1Q)) return false;
    board.make_move(bxa1Q);
    board.unmake_move(bxa1Q);

    auto bxa1R = Move(Square::B2, Square::A1, MoveFlag::ROOK_PROMOTE_CAPTURE);
    if(!test_basics_of_move(board, bxa1R)) return false;
    board.make_move(bxa1R);
    board.unmake_move(bxa1R);

    auto bxa1B = Move(Square::B2, Square::A1, MoveFlag::BISHOP_PROMOTE_CAPTURE);
    if(!test_basics_of_move(board, bxa1B)) return false;
    board.make_move(bxa1B);
    board.unmake_move(bxa1B);

    auto bxa1K = Move(Square::B2, Square::A1, MoveFlag::KNIGHT_PROMOTE_CAPTURE);
    if(!test_basics_of_move(board, bxa1K)) return false;
    board.make_move(bxa1K);

    board.unmake_move(bxa1K);
    board.unmake_move(Kb8);
    board.unmake_move(b3b2);
    board.unmake_move(Ka6);
    board.unmake_move(b4b3);
    board.unmake_move(axb8K);
    board.unmake_move(b5b4);
    board.unmake_move(a6a7);
    board.unmake_move(Rb7);
    board.unmake_move(Kc3);
    board.unmake_move(Ra7);
    board.unmake_move(a5a6);
    board.unmake_move(b7b5);
    board.unmake_move(bxa5);
    board.unmake_move(a7a5);
    board.unmake_move(b2b4);

    auto constexpr new_board = Board();
    return board == new_board;
}

auto constexpr test_make_unmake() noexcept -> bool {
    static_assert(test_scandinavian(), "Scandinavian Make Move");
    static_assert(test_king_side_castle(), "King Side Castle Make Move");
    static_assert(test_queen_side_castle(), "Queen Side Castle Make Move");
    static_assert(test_en_passant(), "En Passant Make Move");
    static_assert(test_promotion(), "Promotion");

    return true;
}

auto constexpr test_board() noexcept -> bool {
    static_assert(test_construct(), "Construct");
    static_assert(test_board_equality(), "Equality");
    static_assert(test_make_unmake(), "Make/Unmake Move");
    return true;
}