/**
* @author Steven Goldade
* @date 10/3/2023
*/
#pragma once
#include <nespp/array.h>
#include <nespp/types.h>
#include "side.h"
#include "square.h"

namespace chess {
    enum class BasicPieceType : u8 {
        NONE = 0,
        PAWN = 1,
        KNIGHT = 2,
        BISHOP = 3,
        ROOK = 4,
        QUEEN = 5,
        KING = 6
    };

    struct PieceType {
        enum Value : u8 {
            NONE = 0,
            WHITE_PAWN = 1,
            WHITE_KNIGHT = 2,
            WHITE_BISHOP = 3,
            WHITE_ROOK = 4,
            WHITE_QUEEN = 5,
            WHITE_KING = 6,
            BLACK_PAWN = 7,
            BLACK_KNIGHT = 8,
            BLACK_BISHOP = 9,
            BLACK_ROOK = 10,
            BLACK_QUEEN = 11,
            BLACK_KING = 12
        };

        constexpr PieceType() noexcept : value(PieceType::NONE) {};
        constexpr PieceType(const PieceType& other) noexcept = default;
        explicit constexpr PieceType(const u8 value) noexcept : value(static_cast<Value>(value)) {}
        constexpr PieceType(const Value value) noexcept : value(value) {} // NOLINT(*-explicit-constructor)
        constexpr PieceType(const BasicPieceType piece_type, bool is_black) noexcept : value(piece_type == BasicPieceType::NONE ? PieceType::NONE : static_cast<Value>(static_cast<u8>(piece_type) + (is_black ? 6 : 0))) {}
        constexpr PieceType(const BasicPieceType piece_type, Side side) noexcept : PieceType(side == Side::NONE ? BasicPieceType::NONE : piece_type, side == Side::BLACK){}

        constexpr operator Value() const noexcept { return value; }// NOLINT(*-explicit-constructor)
        constexpr explicit operator u8() const noexcept { return value; }
        constexpr explicit operator bool() const = delete;

        constexpr explicit operator Side() const noexcept {
            return side();
        }

        [[nodiscard]] auto constexpr side() const noexcept -> Side {
            return is_white() ? Side::WHITE : is_black() ? Side::BLACK
                                                         : Side::NONE;
        }

        [[nodiscard]] auto constexpr opposing_side() const noexcept -> Side {
            return is_white() ? Side::BLACK : is_black() ? Side::WHITE
                                                         : Side::NONE;
        }

        [[nodiscard]] auto constexpr opposes(Side side) const noexcept -> bool {
            return opposing_side() == side;
        }

        [[nodiscard]] auto constexpr opposes(const PieceType& other) const noexcept -> bool {
            return opposing_side() == other.side();
        }

        [[nodiscard]] auto constexpr is_white() const noexcept -> bool {
            return value > NONE && value < BLACK_PAWN;
        }
        
        [[nodiscard]] auto constexpr is_black() const noexcept -> bool {
            return value >= BLACK_PAWN;
        }

        [[nodiscard]] auto constexpr is_none() const noexcept -> bool {
            return value == NONE;
        }

        constexpr explicit operator BasicPieceType() const noexcept {
            return basic_piece_type();
        }

        [[nodiscard]] auto constexpr basic_piece_type() const noexcept -> BasicPieceType {
            switch(value) {
                case NONE:
                    return BasicPieceType::NONE;
                case WHITE_PAWN:
                case BLACK_PAWN:
                    return BasicPieceType::PAWN;
                case WHITE_KNIGHT:
                case BLACK_KNIGHT:
                    return BasicPieceType::KNIGHT;
                case WHITE_BISHOP:
                case BLACK_BISHOP:
                    return BasicPieceType::BISHOP;
                case WHITE_ROOK:
                case BLACK_ROOK:
                    return BasicPieceType::ROOK;
                case WHITE_QUEEN:
                case BLACK_QUEEN:
                    return BasicPieceType::QUEEN;
                case WHITE_KING:
                case BLACK_KING:
                    return BasicPieceType::KING;
            }
        }

        [[nodiscard]] auto constexpr is_pawn() const noexcept -> bool {
            return basic_piece_type() == BasicPieceType::PAWN;
        }

        [[nodiscard]] auto constexpr is_knight() const noexcept -> bool {
            return basic_piece_type() == BasicPieceType::KNIGHT;
        }

        [[nodiscard]] auto constexpr is_bishop() const noexcept -> bool {
            return basic_piece_type() == BasicPieceType::BISHOP;
        }

        [[nodiscard]] auto constexpr is_rook() const noexcept -> bool {
            return basic_piece_type() == BasicPieceType::ROOK;
        }

        [[nodiscard]] auto constexpr is_queen() const noexcept -> bool {
            return basic_piece_type() == BasicPieceType::QUEEN;
        }

        [[nodiscard]] auto constexpr is_king() const noexcept -> bool {
            return basic_piece_type() == BasicPieceType::KING;
        }

        [[nodiscard]] auto constexpr is_opposing_type(Side side, BasicPieceType piece_type) const noexcept -> bool {
            return opposing_side() == side && piece_type == basic_piece_type();
        }

        auto constexpr operator=(const PieceType& other) noexcept -> PieceType& = default;
    private:
        Value value;
    };

    struct Piece {
        constexpr Piece() noexcept : internal_piece_type(PieceType::NONE), internal_square(Square::INVALID) {}
        constexpr Piece(const PieceType& type, const Square& square) noexcept : internal_piece_type(type), internal_square(square) {};

        [[nodiscard]] auto constexpr square() const noexcept -> const Square& {
            return internal_square;
        }

        [[nodiscard]] auto constexpr piece_type() const noexcept -> const PieceType& {
            return internal_piece_type;
        }

        [[nodiscard]] auto constexpr is_none() const noexcept -> bool {
            return internal_piece_type.is_none();
        }

        [[nodiscard]] auto constexpr is_pawn() const noexcept -> bool {
            return internal_piece_type.is_pawn();
        }

        [[nodiscard]] auto constexpr is_knight() const noexcept -> bool {
            return internal_piece_type.is_knight();
        }

        [[nodiscard]] auto constexpr is_bishop() const noexcept -> bool {
            return internal_piece_type.is_bishop();
        }

        [[nodiscard]] auto constexpr is_rook() const noexcept -> bool {
            return internal_piece_type.is_rook();
        }

        [[nodiscard]] auto constexpr is_queen() const noexcept -> bool {
            return internal_piece_type.is_queen();
        }

        [[nodiscard]] auto constexpr is_king() const noexcept -> bool {
            return internal_piece_type.is_king();
        }

        [[nodiscard]] auto constexpr side() const noexcept -> Side {
            return internal_piece_type.side();
        }

        [[nodiscard]] auto constexpr opposing_side() const noexcept -> Side {
            return internal_piece_type.opposing_side();
        }

        [[nodiscard]] auto constexpr is_white() const noexcept -> bool {
            return side() == Side::WHITE;
        }

        [[nodiscard]] auto constexpr is_black() const noexcept -> bool {
            return side() == Side::BLACK;
        }

        [[nodiscard]] auto constexpr opposes(const Side side) const noexcept -> bool {
            return internal_piece_type.opposes(side);
        }

        [[nodiscard]] auto constexpr opposes(const Piece& other) const noexcept -> bool {
            return internal_piece_type.opposes(other.internal_piece_type);
        }

        auto constexpr demote() noexcept -> void {
            promote(BasicPieceType::PAWN);
        }

        auto constexpr promote(BasicPieceType piece_type) noexcept -> void {
            internal_piece_type = PieceType(piece_type, internal_piece_type.side());
        }

        auto constexpr move(const Square& square) noexcept -> void {
            internal_square = square;
        }

        auto constexpr operator==(const Piece& other) const noexcept -> bool {
            return internal_square == other.internal_square && internal_piece_type == other.internal_piece_type;
        }
    private:
        PieceType internal_piece_type;
        Square internal_square;
    };
}// namespace chess
