/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include <chess/move_generator.h>

using namespace chess;

auto constexpr test_starting_pawn(const Square& square) -> bool {
    auto constexpr start_position = Position();

    auto start_pawn = start_position.get_board().piece_at(square);
    auto pawn_moves = MoveGenerator::pawn_moves(start_position, start_pawn);

    if(pawn_moves.size() != 2) return false;
    if(!pawn_moves.contains(Move(square, square.north()))) return false;
    if(!pawn_moves.contains(Move(square, square.north().north(), MoveFlag::DOUBLE_PAWN_PUSH))) return false;

    return true;
}

auto constexpr test_pawn_moves() noexcept -> bool {
    static_assert(test_starting_pawn(Square::A2));
    static_assert(test_starting_pawn(Square::B2));
    static_assert(test_starting_pawn(Square::C2));
    static_assert(test_starting_pawn(Square::D2));
    static_assert(test_starting_pawn(Square::E2));
    static_assert(test_starting_pawn(Square::F2));
    static_assert(test_starting_pawn(Square::G2));
    static_assert(test_starting_pawn(Square::H2));

    auto constexpr pawn_position = Position("rnb1kbnr/ppp1p1pp/3q4/3pPp2/8/5N2/PPPP1PPP/RNBQKB1R w KQkq f6 0 4");
    auto constexpr e5_pawn = pawn_position.get_board().piece_at(Square::E5);
    auto constexpr e5_pawn_moves = MoveGenerator::pawn_moves(pawn_position, e5_pawn);
    static_assert(e5_pawn_moves.size() == 3);
    static_assert(e5_pawn_moves.contains(Move(Square::E5, Square::D6, MoveFlag::CAPTURE)));
    static_assert(e5_pawn_moves.contains(Move(Square::E5, Square::F6, MoveFlag::EN_PASSANT)));
    static_assert(e5_pawn_moves.contains(Move(Square::E5, Square::E6)));

    auto constexpr position3 = Position("r1bqkbnr/1P1ppppp/2n5/p1p5/8/8/PP1PPPPP/RNBQKBNR w KQkq - 1 5");
    auto constexpr b7_pawn = position3.get_board().piece_at(Square::B7);
    auto constexpr b7_pawn_moves = MoveGenerator::pawn_moves(position3, b7_pawn);
    static_assert(b7_pawn_moves.size() == 12);
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::A8, MoveFlag::QUEEN_PROMOTE_CAPTURE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::A8, MoveFlag::ROOK_PROMOTE_CAPTURE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::A8, MoveFlag::BISHOP_PROMOTE_CAPTURE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::A8, MoveFlag::KNIGHT_PROMOTE_CAPTURE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::C8, MoveFlag::QUEEN_PROMOTE_CAPTURE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::C8, MoveFlag::ROOK_PROMOTE_CAPTURE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::C8, MoveFlag::BISHOP_PROMOTE_CAPTURE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::C8, MoveFlag::KNIGHT_PROMOTE_CAPTURE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::B8, MoveFlag::QUEEN_PROMOTE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::B8, MoveFlag::ROOK_PROMOTE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::B8, MoveFlag::BISHOP_PROMOTE)));
    static_assert(b7_pawn_moves.contains(Move(Square::B7, Square::B8, MoveFlag::KNIGHT_PROMOTE)));

    return true;
}

auto constexpr test_knight_moves() noexcept -> bool {
    auto constexpr position = Position();

    auto constexpr b1_knight = position.get_board().piece_at(Square::B1);
    auto constexpr b1_knight_moves = MoveGenerator::knight_moves(position, b1_knight);
    static_assert(b1_knight_moves.size() == 2);
    static_assert(b1_knight_moves.contains(Move(Square::B1, Square::C3)));
    static_assert(b1_knight_moves.contains(Move(Square::B1, Square::A3)));

    auto constexpr g1_knight = position.get_board().piece_at(Square::G1);
    auto constexpr g1_knight_moves = MoveGenerator::knight_moves(position, g1_knight);
    static_assert(g1_knight_moves.size() == 2);
    static_assert(g1_knight_moves.contains(Move(Square::G1, Square::F3)));
    static_assert(g1_knight_moves.contains(Move(Square::G1, Square::H3)));

    auto constexpr capture_7 = Position("8/8/2q1q3/1q3q2/3N4/5q2/2q1q3/8 w - - 0 9");
    auto constexpr d4_knight = capture_7.get_board().piece_at(Square::D4);
    auto constexpr d4_knight_moves = MoveGenerator::knight_moves(capture_7, d4_knight);
    static_assert(d4_knight_moves.size() == 8);
    static_assert(d4_knight_moves.contains(Move(Square::D4, Square::B5, MoveFlag::CAPTURE)));
    static_assert(d4_knight_moves.contains(Move(Square::D4, Square::C6, MoveFlag::CAPTURE)));
    static_assert(d4_knight_moves.contains(Move(Square::D4, Square::E6, MoveFlag::CAPTURE)));
    static_assert(d4_knight_moves.contains(Move(Square::D4, Square::F5, MoveFlag::CAPTURE)));
    static_assert(d4_knight_moves.contains(Move(Square::D4, Square::F3, MoveFlag::CAPTURE)));
    static_assert(d4_knight_moves.contains(Move(Square::D4, Square::E2, MoveFlag::CAPTURE)));
    static_assert(d4_knight_moves.contains(Move(Square::D4, Square::C2, MoveFlag::CAPTURE)));
    static_assert(d4_knight_moves.contains(Move(Square::D4, Square::B3)));

    return true;
}

auto constexpr test_bishop_moves() noexcept -> bool {
    auto constexpr start_position = Position();

    auto constexpr c1_bishop = start_position.get_board().piece_at(Square::C1);
    auto constexpr c1_bishop_moves = MoveGenerator::bishop_moves(start_position, c1_bishop);
    static_assert(c1_bishop_moves.empty());

    auto constexpr f1_bishop = start_position.get_board().piece_at(Square::F1);
    auto constexpr f1_bishop_moves = MoveGenerator::bishop_moves(start_position, f1_bishop);
    static_assert(f1_bishop_moves.empty());

    auto constexpr bishop_position = Position("7q/p7/8/8/3B4/8/1N6/6r1 w - - 0 9");
    auto constexpr d4_bishop = bishop_position.get_board().piece_at(Square::D4);
    auto constexpr d4_bishop_moves = MoveGenerator::bishop_moves(bishop_position, d4_bishop);
    static_assert(d4_bishop_moves.size() == 11);
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::C5)));
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::B6)));
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::A7, MoveFlag::CAPTURE)));
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::E5)));
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::F6)));
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::G7)));
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::H8, MoveFlag::CAPTURE)));
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::E3)));
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::F2)));
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::G1, MoveFlag::CAPTURE)));
    static_assert(d4_bishop_moves.contains(Move(Square::D4, Square::C3)));
    return true;
}

auto constexpr test_rook_moves() noexcept -> bool {
    auto constexpr start_position = Position();

    auto constexpr a1_rook = start_position.get_board().piece_at(Square::A1);
    auto constexpr a1_rook_moves = MoveGenerator::rook_moves(start_position, a1_rook);
    static_assert(a1_rook_moves.empty());

    auto constexpr h1_rook = start_position.get_board().piece_at(Square::H1);
    auto constexpr h1_rook_moves = MoveGenerator::rook_moves(start_position, h1_rook);
    static_assert(h1_rook_moves.empty());

    auto constexpr rook_position = Position("2q5/8/8/8/n1R4b/8/8/2Q5 w - - 0 9");
    auto constexpr c4_rook = rook_position.get_board().piece_at(Square::C4);
    auto constexpr c4_rook_moves = MoveGenerator::rook_moves(rook_position, c4_rook);
    static_assert(c4_rook_moves.size() == 13);
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::C5)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::C6)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::C7)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::C8, MoveFlag::CAPTURE)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::D4)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::E4)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::F4)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::G4)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::H4, MoveFlag::CAPTURE)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::C3)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::C2)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::B4)));
    static_assert(c4_rook_moves.contains(Move(Square::C4, Square::A4, MoveFlag::CAPTURE)));

    return true;
}

auto constexpr test_queen_moves() noexcept -> bool {
    auto constexpr start_position = Position();

    auto constexpr d1_queen = start_position.get_board().piece_at(Square::D1);
    auto constexpr d1_queen_moves = MoveGenerator::queen_moves(start_position, d1_queen);
    static_assert(d1_queen_moves.empty());

    auto constexpr queen_position = Position("1r2r2b/8/8/P3Qp2/8/2n5/7n/4q3 w - - 0 9");
    auto constexpr e5_queen = queen_position.get_board().piece_at(Square::E5);
    auto constexpr e5_queen_moves = MoveGenerator::queen_moves(queen_position, e5_queen);
    static_assert(e5_queen_moves.size() == 22);
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::E6)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::E7)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::E8, MoveFlag::CAPTURE)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::F6)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::G7)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::H8, MoveFlag::CAPTURE)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::F5, MoveFlag::CAPTURE)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::F4)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::G3)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::H2, MoveFlag::CAPTURE)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::E4)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::E3)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::E2)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::E1, MoveFlag::CAPTURE)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::D4)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::C3, MoveFlag::CAPTURE)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::D5)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::C5)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::B5)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::D6)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::C7)));
    static_assert(e5_queen_moves.contains(Move(Square::E5, Square::B8, MoveFlag::CAPTURE)));

    return true;
}

auto constexpr test_king_moves() noexcept -> bool {
    auto constexpr start_position = Position();

    auto constexpr e1_king = start_position.get_board().piece_at(Square::E1);
    auto constexpr e1_king_moves = MoveGenerator::king_moves(start_position, e1_king);

    static_assert(e1_king_moves.empty());

    return true;
}

auto constexpr test_in_check() noexcept -> bool {
    auto constexpr start_position = Position();

    static_assert(!MoveGenerator::square_attacked_by(start_position, Square::E1, Side::BLACK));
    static_assert(!MoveGenerator::in_check(start_position));


    auto constexpr pos_test = Position("8/2p5/1K1p4/1P5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    static_assert(MoveGenerator::in_check(pos_test));
    return true;
}

auto constexpr perft(Position& position, u8 depth) noexcept -> u32 {
    u32 nodes = 0;
    if(depth == 0) return 1;

    auto moves = MoveGenerator::pseudo_legal_moves(position);
    auto side = position.side_to_move();
    for(auto & move : moves) {
        position.make_move(move);
        if(!MoveGenerator::side_in_check(position, side))
            nodes += perft(position, depth-1);
        position.unmake_move(move);
    }

    return nodes;
}

auto constexpr test_perft() noexcept -> bool {
    auto position = Position();
    if(perft(position, 2) != 400) return false;

    auto kiwipete = Position("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0");
    if(perft(kiwipete, 2) != 2039) return false;

    auto position3 = Position("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0");
    if(perft(position3, 2) != 191) return false;

    auto position4 = Position("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    if(perft(position4, 2) != 264) return false;

    auto position5 = Position("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    if(perft(position5, 2) != 1486) return false;

    auto position6 = Position("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
    if(perft(position6, 2) != 2079) return false;

    return true;
}

auto constexpr test_move_generator() noexcept -> bool {
    static_assert(test_pawn_moves());
    static_assert(test_knight_moves());
    static_assert(test_bishop_moves());
    static_assert(test_rook_moves());
    static_assert(test_queen_moves());
    static_assert(test_king_moves());
    static_assert(test_in_check());
    //static_assert(test_perft()); //Commented out to save compile time.. since these are compile time tests

    return true;
}