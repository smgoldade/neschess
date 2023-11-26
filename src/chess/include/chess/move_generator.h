/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include "board.h"
#include "position.h"
#include <nespp/vector.h>

namespace chess::MoveGenerator {

    [[nodiscard]] auto constexpr knight_move_squares(const Square& square) noexcept -> nespp::Vector<Square, 8> {
        auto moves = nespp::Vector<Square, 8>();
        if(!square.is_valid()) return moves;

        auto const knight_1 = square.knight_1();
        if(knight_1.is_valid()) moves.push_back(knight_1);
        auto const knight_2 = square.knight_2();
        if(knight_2.is_valid()) moves.push_back(knight_2);
        auto const knight_3 = square.knight_3();
        if(knight_3.is_valid()) moves.push_back(knight_3);
        auto const knight_4 = square.knight_4();
        if(knight_4.is_valid()) moves.push_back(knight_4);
        auto const knight_5 = square.knight_5();
        if(knight_5.is_valid()) moves.push_back(knight_5);
        auto const knight_6 = square.knight_6();
        if(knight_6.is_valid()) moves.push_back(knight_6);
        auto const knight_7 = square.knight_7();
        if(knight_7.is_valid()) moves.push_back(knight_7);
        auto const knight_8 = square.knight_8();
        if(knight_8.is_valid()) moves.push_back(knight_8);
        
        return moves;
    }

    auto constexpr square_attacked_by(const Position& position, const Square& square, const Side side) noexcept -> bool {
        auto const & board = position.get_board();

        for(auto const direction : DIRECTIONS) {
            auto target_square = square.ray(direction);
            auto immediate = true;
            while(target_square.is_valid()) {
                auto const piece = board.piece_at(target_square);
                if(piece.is_none()) {
                    immediate = false;
                    target_square = target_square.ray(direction);
                    continue;
                }
                if(piece.side() == side) {
                    switch(direction) {
                        case Direction::NORTH:
                        case Direction::EAST:
                        case Direction::SOUTH:
                        case Direction::WEST:
                            if(immediate && piece.is_king()) return true;
                            if(piece.is_rook() || piece.is_queen()) return true;
                            break;
                        case Direction::NORTHEAST:
                        case Direction::NORTHWEST:
                            if(immediate) {
                                if(piece.is_king()) return true;
                                if(piece.is_pawn() && piece.is_black()) return true;
                            }
                            if(piece.is_bishop() || piece.is_queen()) return true;
                            break;
                        case Direction::SOUTHEAST:
                        case Direction::SOUTHWEST:
                            if(immediate) {
                                if(piece.is_king()) return true;
                                if(piece.is_pawn() && piece.is_white()) return true;
                            }
                            if(piece.is_bishop() || piece.is_queen()) return true;
                            break;
                    }
                }
                break;
            }
        }

        auto const knight_squares = knight_move_squares(square);
        return container_any(knight_squares, [&](const Square& knight_square) { return board.piece_at(knight_square).piece_type() == PieceType(BasicPieceType::KNIGHT, side); });
    }

    auto constexpr pawn_moves(const Position& position, const Piece& pawn_piece) noexcept -> nespp::Vector<Move, 12> {
        auto moves = nespp::Vector<Move, 12>();
        auto const & board = position.get_board();
        auto const pawn_side = pawn_piece.side();
        auto const & pawn_square = pawn_piece.square();

        auto const white = (pawn_side == Side::WHITE);
        auto const push_square = white ? pawn_square.north() : pawn_square.south();
        auto const promotion = push_square.rank() == (white ? Rank::_8 : Rank::_1);
        auto const double_push = pawn_square.rank() == (white ? Rank::_2 : Rank::_7);
        auto const west_capture = push_square.west();
        auto const east_capture = push_square.east();
        auto const & en_passant_square = position.get_en_passant_square();
        auto const ep_valid = en_passant_square.is_valid();

        if(ep_valid && (en_passant_square == west_capture || en_passant_square == east_capture)) {
            moves.push_back(Move(pawn_square, en_passant_square, MoveFlag::EN_PASSANT));
        }

        auto const maybe_add_pawn_captures = [&](const Square& capture_square) {
            auto const capture_piece = board.piece_at(capture_square);
            if(!capture_piece.opposes(pawn_piece)) return;
            if(promotion) {
                moves.push_back(Move(pawn_square, capture_square, MoveFlag::QUEEN_PROMOTE_CAPTURE));
                moves.push_back(Move(pawn_square, capture_square, MoveFlag::ROOK_PROMOTE_CAPTURE));
                moves.push_back(Move(pawn_square, capture_square, MoveFlag::BISHOP_PROMOTE_CAPTURE));
                moves.push_back(Move(pawn_square, capture_square, MoveFlag::KNIGHT_PROMOTE_CAPTURE));
            } else {
                moves.push_back(Move(pawn_square, capture_square, MoveFlag::CAPTURE));
            }
        };
        maybe_add_pawn_captures(west_capture);
        maybe_add_pawn_captures(east_capture);

        if(board.no_piece_at(push_square)) {
            if(promotion) {
                moves.push_back(Move(pawn_square, push_square, MoveFlag::QUEEN_PROMOTE));
                moves.push_back(Move(pawn_square, push_square, MoveFlag::ROOK_PROMOTE));
                moves.push_back(Move(pawn_square, push_square, MoveFlag::BISHOP_PROMOTE));
                moves.push_back(Move(pawn_square, push_square, MoveFlag::KNIGHT_PROMOTE));
            } else {
                moves.push_back(Move(pawn_square, push_square));
                if(double_push) {
                    auto double_push_square = white ? push_square.north() : push_square.south();
                    if(board.no_piece_at(double_push_square)) moves.push_back(Move(pawn_square, double_push_square, MoveFlag::DOUBLE_PAWN_PUSH));
                }
            }
        }
        return moves;
    }

    auto constexpr knight_moves(const Position& position, const Piece& knight_piece) noexcept -> nespp::Vector<Move, 8> {
        auto const & board = position.get_board();
        auto const & knight_square = knight_piece.square();
        auto const knight_moves = knight_move_squares(knight_square);

        auto captures = nespp::Vector<Move,8>();
        auto quiet = nespp::Vector<Move,8>();

        for(auto const & target_square : knight_moves) {
            auto const target_piece = board.piece_at(target_square);
            if(target_piece.is_none()) quiet.push_back(Move(knight_square, target_square));
            if(target_piece.opposes(knight_piece)) captures.push_back(Move(knight_square, target_square, MoveFlag::CAPTURE));
        }
        captures.push_back_all(quiet);
        return captures;
    }


    template<size_t SIZE, size_t RETURN_SIZE>
    auto constexpr ray_moves(const Position& position, const Piece& ray_piece, const nespp::Array<Direction, SIZE>& directions) noexcept -> nespp::Vector<Move, RETURN_SIZE> {
        auto captures = nespp::Vector<Move, RETURN_SIZE>();
        auto quiet = nespp::Vector<Move, RETURN_SIZE>();

        auto const & board = position.get_board();
        auto const & source_square = ray_piece.square();
        for(auto const direction : directions) {
            auto target_square = source_square.ray(direction);
            while(target_square.is_valid()) {
                auto const target_piece = board.piece_at(target_square);
                if(target_piece.is_none()) {
                    quiet.push_back(Move(source_square, target_square));
                    target_square = target_square.ray(direction);
                    continue;
                }
                if(target_piece.opposes(ray_piece)) captures.push_back(Move(source_square, target_square, MoveFlag::CAPTURE));
                break;
            }
        }
        captures.push_back_all(quiet);
        return captures;
    }

    auto constexpr bishop_moves(const Position& position, const Piece& bishop_piece) noexcept -> nespp::Vector<Move, 13> {
        return ray_moves<4, 13>(position, bishop_piece, DIAGONALS);
    }

    auto constexpr rook_moves(const Position& position, const Piece& rook_piece) noexcept -> nespp::Vector<Move, 14> {
        return ray_moves<4, 14>(position, rook_piece, CARDINALS);
    }

    auto constexpr queen_moves(const Position& position, const Piece& queen_piece) noexcept -> nespp::Vector<Move, 27> {
        return ray_moves<8, 27>(position, queen_piece, DIRECTIONS);
    }

    auto constexpr king_moves(const Position& position, const Piece& king_piece) noexcept -> nespp::Vector<Move,8> {
        auto captures = nespp::Vector<Move, 8>();
        auto quiet = nespp::Vector<Move, 8>();
        auto const & board = position.get_board();
        auto const & king_square = king_piece.square();

        for(auto const direction : DIRECTIONS) {
            auto const target_square = king_square.ray(direction);
            if(!target_square.is_valid()) continue;

            auto const target_piece = board.piece_at(target_square);
            if(target_piece.is_none()) quiet.push_back(Move(king_square, target_square));
            if(target_piece.opposes(king_piece)) captures.push_back(Move(king_square, target_square, MoveFlag::CAPTURE));
        }

        auto const king_attacked = square_attacked_by(position, king_square, king_piece.opposing_side());
        auto const maybe_add_castle_to_side = [&](const bool side_castle, const Direction direction, const MoveFlag castle_move_flag) {
            if(king_attacked) return;
            if(!side_castle) return;

            auto const move_1 = king_square.ray(direction);
            auto const move_2 = move_1.ray(direction);
            auto const move_1_attacked = square_attacked_by(position, move_1, king_piece.opposing_side());
            auto const move_2_attacked = square_attacked_by(position, move_2, king_piece.opposing_side());
            auto const move_1_empty = board.no_piece_at(move_1);
            auto const move_2_empty = board.no_piece_at(move_2);

            if(move_1_empty && move_2_empty && !move_1_attacked && !move_2_attacked)
                captures.push_back(Move(king_square, move_2, castle_move_flag));
        };
        maybe_add_castle_to_side(king_piece.is_white() ? position.can_white_king_side_castle() : position.can_black_king_side_castle(), Direction::EAST, MoveFlag::KING_SIDE_CASTLE);
        maybe_add_castle_to_side(king_piece.is_white() ? position.can_white_queen_side_castle() : position.can_black_queen_side_castle(), Direction::WEST, MoveFlag::QUEEN_SIDE_CASTLE);

        captures.push_back_all(quiet);
        return captures;
    }

    auto constexpr moves_for_piece(const Position& position, const Piece& piece) noexcept -> nespp::Vector<Move, 27> {
        auto const basic_type = piece.piece_type().basic_piece_type();

        switch(basic_type) {
            case BasicPieceType::NONE:
                return {};
            case BasicPieceType::PAWN:
                return nespp::Vector<Move,27>{pawn_moves(position, piece)};
            case BasicPieceType::KNIGHT:
                return nespp::Vector<Move,27>{knight_moves(position, piece)};
            case BasicPieceType::BISHOP:
                return nespp::Vector<Move,27>{bishop_moves(position, piece)};
            case BasicPieceType::ROOK:
                return nespp::Vector<Move,27>{rook_moves(position, piece)};
            case BasicPieceType::QUEEN:
                return queen_moves(position, piece);
            case BasicPieceType::KING:
                return nespp::Vector<Move,27>{king_moves(position, piece)};
        }
    }

    auto constexpr pseudo_legal_moves(const Position& position) noexcept -> nespp::Vector<Move, 64> {
        auto moves = nespp::Vector<Move, 64>();
        auto const & board = position.get_board();
        auto const side = position.side_to_move();

        auto const & pieces = board.get_pieces(side);
        for(auto const & piece : pieces) {
            if(!piece.square().is_valid()) continue;
            moves.push_back_all(moves_for_piece(position, piece));
        }

        return moves;
    }

    auto constexpr side_in_check(const Position& position, const Side side) noexcept -> bool {
        auto const & board = position.get_board();
        auto const & king_square = board.get_king_square(side);
        return square_attacked_by(position, king_square, opposing_side(side));
    }

    auto constexpr in_check(const Position& position) noexcept -> bool {
        return side_in_check(position, position.side_to_move());
    }

    auto constexpr is_move_legal(Position& position, const Move& move) noexcept -> bool {
        auto const side = position.side_to_move();

        auto const scoped_move = position.make_scoped_move(move);
        return !side_in_check(position, side);
    }

    auto constexpr in_checkmate(Position& position) noexcept -> bool {
        if(!side_in_check(position, position.side_to_move())) return false;
        auto const moves_for_king = king_moves(position, position.get_board().get_pieces(position.side_to_move()).get_king());
        return container_all(moves_for_king, [&](const Move& move) {return !is_move_legal(position, move);});
    }
}