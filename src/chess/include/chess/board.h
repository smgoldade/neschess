// Author: Steven Goldade
#pragma once
#include "move.h"
#include "piece.h"
#include "piece_set.h"
#include <nespp/nesmath.h>
#include <nespp/stack.h>

namespace chess {
    struct Board {
        constexpr Board() noexcept : board{
            PieceType::WHITE_ROOK, PieceType::WHITE_KNIGHT, PieceType::WHITE_BISHOP, PieceType::WHITE_QUEEN, PieceType::WHITE_KING, PieceType::WHITE_BISHOP, PieceType::WHITE_KNIGHT, PieceType::WHITE_ROOK,
            PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN,
            PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE,
            PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE,
            PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE,
            PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE,
            PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN,
            PieceType::BLACK_ROOK, PieceType::BLACK_KNIGHT, PieceType::BLACK_BISHOP, PieceType::BLACK_QUEEN, PieceType::BLACK_KING, PieceType::BLACK_BISHOP, PieceType::BLACK_KNIGHT, PieceType::BLACK_ROOK,
        }, white_pieces(false),  white_king_square(Square::E1), black_pieces(true), black_king_square(Square::E8) {}

        explicit constexpr Board(const PieceType board[64]) noexcept : board(), white_pieces(false, true), black_pieces(true, true) {
            for(u8 i=0; i<64; i++) {
                auto const piece = board[i];
                auto const square = Square(i, false);
                if(piece.is_white()) {
                    auto wp = white_pieces.grab_invalid(piece);
                    wp.piece = Piece(piece, square);
                    if(piece.is_king()) white_king_square = square;
                }
                if(piece.is_black()) {
                    auto bp = black_pieces.grab_invalid(piece);
                    bp.piece = Piece(piece, square);
                    if(piece.is_king()) black_king_square = square;
                }
                this->board[i] = board[i];
            }

        }
    
        auto constexpr make_move(const Move& move) noexcept -> void {
            auto from = move.from_square();
            auto to = move.to_square();
            
            auto fp = grab_piece(from);
            auto from_piece = grab_piece_reference(fp);
            from_piece.piece.move(to);
            if(move.is_promotion()) {
                from_piece.piece.promote(move.promote_piece_type());
                from_piece.mark_cleanup();
            }

            if(move.is_capture()) {
                auto tp = grab_piece(move.is_en_passant() ? move.en_passant_square() : to);
                auto to_piece = grab_piece_reference(tp);
                to_piece.piece.move(Square::INVALID);
                to_piece.mark_cleanup();
                capture_stack.push(to_piece.piece.piece_type());
            }
            set_piece(from_piece);

            if(from_piece.piece.piece_type() == PieceType::WHITE_KING) white_king_square = to;
            if(from_piece.piece.piece_type() == PieceType::BLACK_KING) black_king_square = to;
            if(!move.is_castle()) return;

            if(move.is_king_side_castle()) {
                auto white = from == Square::E1;
                auto rp = grab_piece(white ? Square::H1 : Square::H8);
                auto const & rook = grab_piece_reference(rp);
                rook.piece.move(white ? Square::F1 : Square::F8);
                set_piece(rook);
            }
            if(move.is_queen_side_castle()) {
                auto white = from == Square::E1;
                auto rp = grab_piece(white ? Square::A1 : Square::A8);
                auto const & rook = grab_piece_reference(rp);
                rook.piece.move(white ? Square::D1 : Square::D8);
                set_piece(rook);
            }
        }
    
        auto constexpr unmake_move(const Move& move) noexcept -> void {
            auto from = move.from_square();
            auto to = move.to_square();
    
            auto tp = grab_piece(to);
            auto to_piece = grab_piece_reference(tp);
            to_piece.piece.move(from);
            if(move.is_promotion()) {
                to_piece.piece.demote();
                to_piece.mark_cleanup();
            }
            set_piece(to_piece);

            if(move.is_capture()) {
                auto & from_piece_type = capture_stack.pop();
                auto fp = Piece {from_piece_type, Square::INVALID};
                auto from_piece = grab_captured_piece_reference(fp);
                from_piece.piece.move(move.is_en_passant() ? move.en_passant_square() : to);
                from_piece.mark_cleanup();
                set_piece(from_piece);
            }

            if(to_piece.piece.piece_type() == PieceType::WHITE_KING) white_king_square = from;
            if(to_piece.piece.piece_type() == PieceType::BLACK_KING) black_king_square = from;
            if(!move.is_castle()) return;
            if(move.is_king_side_castle()) {
                auto white = from == Square::E1;
                auto rp = grab_piece(white ? Square::F1 : Square::F8);
                auto const & rook = grab_piece_reference(rp);
                rook.piece.move(white ? Square::H1 : Square::H8);
                set_piece(rook);
            }
            if(move.is_queen_side_castle()) {
                auto white = from == Square::E1;
                auto rp = grab_piece(white ? Square::D1 : Square::D8);
                auto const & rook = grab_piece_reference(rp);
                rook.piece.move(white ? Square::A1 : Square::A8);
                set_piece(rook);
            }
        }
        
        [[nodiscard]] auto constexpr piece_at(const Square& square) const noexcept -> Piece {
            if(!square.is_valid()) return {PieceType::NONE, square};
            return {board[square.as_8x8_square_index()], square};
        }

        [[nodiscard]] auto constexpr no_piece_at(const Square& square) const noexcept -> bool {
            return piece_at(square).is_none();
        }

        [[nodiscard]] auto constexpr get_king_square(const Side side) const noexcept -> const Square& {
            return side == Side::WHITE ? white_king_square : black_king_square;
        }

        [[nodiscard]] auto constexpr get_pieces(const Side side) const noexcept -> const PieceSet& {
            return side == Side::WHITE ? white_pieces : black_pieces;
        }

        auto constexpr operator==(const Board& other) const noexcept -> bool {
            for(u8 i=0; i<64; ++i) {
                if(board[i] != other.board[i]) return false;
            }
            return true; //capture_stack == other.capture_stack;
        }
    private:
        auto constexpr grab_piece(const Square& square) -> Piece {
            auto type = board[square.as_8x8_square_index()];
            board[square.as_8x8_square_index()] = PieceType::NONE;
            return {type, square};
        }

        auto constexpr grab_piece_reference(Piece& piece) -> PieceSet::ReferencedPiece {
            if(piece.side() == Side::WHITE) return white_pieces.grab_piece(piece);
            if(piece.side() == Side::BLACK) return black_pieces.grab_piece(piece);
            return {piece, 0, nullptr};
        }

        auto constexpr grab_captured_piece_reference(Piece& piece) -> PieceSet::ReferencedPiece {
            if(piece.side() == Side::WHITE) return white_pieces.grab_captured_piece(piece);
            if(piece.side() == Side::BLACK) return black_pieces.grab_captured_piece(piece);
            return {piece, 0, nullptr};
        }

        auto constexpr set_piece(const PieceSet::ReferencedPiece& piece) -> void {
            board[piece.piece.square().as_8x8_square_index()] = piece.piece.piece_type();
        }

        PieceType board[64];
        PieceSet white_pieces;
        Square white_king_square;
        PieceSet black_pieces;
        Square black_king_square;
        nespp::Stack<PieceType, 30> capture_stack;
    };
}