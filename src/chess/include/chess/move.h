// Author: Steven Goldade
#pragma once
#include "piece.h"
#include "square.h"
#include <nespp/types.h>

namespace chess {
    enum class MoveFlag : u8 {
        QUIET = 0,
        DOUBLE_PAWN_PUSH = 1,
        KING_SIDE_CASTLE = 2,
        QUEEN_SIDE_CASTLE = 3,
        CAPTURE = 4,
        EN_PASSANT = 5,
        KNIGHT_PROMOTE = 8,
        BISHOP_PROMOTE = 9,
        ROOK_PROMOTE = 10,
        QUEEN_PROMOTE = 11,
        KNIGHT_PROMOTE_CAPTURE = 12,
        BISHOP_PROMOTE_CAPTURE = 13,
        ROOK_PROMOTE_CAPTURE = 14,
        QUEEN_PROMOTE_CAPTURE = 15
    };

    struct Move {
        static constexpr u16 FROM_SQUARE_MASK = 0x003F;
        static constexpr u16 TO_SQUARE_MASK = 0x0FC0;
        static constexpr u16 FLAG_MASK = 0xF000;

        constexpr Move() : value(0) {}
        constexpr Move(const Square from_square, const Square to_square, const MoveFlag flag) noexcept : value((static_cast<u8>(flag) << 12) + (to_square.as_8x8_square_index() << 6) + static_cast<u8>(from_square.as_8x8_square_index())) {}
        constexpr Move(const Square from_square, const Square to_square) noexcept : value((to_square.as_8x8_square_index() << 6) + from_square.as_8x8_square_index()) {}

        [[nodiscard]] auto constexpr is_null_move() const noexcept -> bool {
            return value == 0;
        }

        [[nodiscard]] auto constexpr from_square() const noexcept -> Square {
            return Square {static_cast<u8>(value & FROM_SQUARE_MASK), false};
        }

        [[nodiscard]] auto constexpr to_square() const noexcept -> Square {
            return Square {static_cast<u8>((value & TO_SQUARE_MASK) >> 6), false};
        }

        [[nodiscard]] auto constexpr flags() const noexcept -> MoveFlag {
            return static_cast<MoveFlag>((value & FLAG_MASK) >> 12);
        }

        [[nodiscard]] auto constexpr is_quiet() const noexcept -> bool {
            return flags() == MoveFlag::QUIET;
        }

        [[nodiscard]] auto constexpr is_capture() const noexcept -> bool {
            return static_cast<u8>(flags()) & static_cast<u8>(MoveFlag::CAPTURE);
        }

        [[nodiscard]] auto constexpr is_en_passant() const noexcept -> bool {
            return flags() == MoveFlag::EN_PASSANT;
        }

        [[nodiscard]] auto constexpr en_passant_square() const noexcept -> Square {
            if(!is_en_passant()) return Square::INVALID;
            auto direction = from_square().direction(to_square());
            if(direction == Direction::NORTHWEST || direction == Direction::NORTHEAST) return to_square().south();
            if(direction == Direction::SOUTHWEST || direction == Direction::SOUTHEAST) return to_square().north();
            return Square::INVALID;
        }

        [[nodiscard]] auto constexpr is_king_side_castle() const noexcept -> bool {
            return flags() == MoveFlag::KING_SIDE_CASTLE;
        }

        [[nodiscard]] auto constexpr is_queen_side_castle() const noexcept -> bool {
            return flags() == MoveFlag::QUEEN_SIDE_CASTLE;
        }

        [[nodiscard]] auto constexpr is_castle() const noexcept -> bool {
            return is_king_side_castle() || is_queen_side_castle();
        }

        [[nodiscard]] auto constexpr is_double_pawn_push() const noexcept -> bool {
            return flags() == MoveFlag::DOUBLE_PAWN_PUSH;
        }

        [[nodiscard]] auto constexpr double_pawn_single_square() const noexcept -> Square {
            if(!is_double_pawn_push()) return Square::INVALID;
            auto direction = from_square().direction(to_square());
            return from_square().ray(direction);
        }

        [[nodiscard]] auto constexpr is_promotion() const noexcept -> bool {
            return flags() >= MoveFlag::KNIGHT_PROMOTE;
        }

        [[nodiscard]] auto constexpr promote_piece_type() const noexcept -> BasicPieceType {
            switch(flags()) {
                case MoveFlag::KNIGHT_PROMOTE:
                case MoveFlag::KNIGHT_PROMOTE_CAPTURE:
                    return BasicPieceType::KNIGHT;
                case MoveFlag::BISHOP_PROMOTE:
                case MoveFlag::BISHOP_PROMOTE_CAPTURE:
                    return BasicPieceType::BISHOP;
                case MoveFlag::ROOK_PROMOTE:
                case MoveFlag::ROOK_PROMOTE_CAPTURE:
                    return BasicPieceType::ROOK;
                case MoveFlag::QUEEN_PROMOTE:
                case MoveFlag::QUEEN_PROMOTE_CAPTURE:
                    return BasicPieceType::QUEEN;
                default:
                    return BasicPieceType::NONE;
            }
        }

        constexpr explicit operator MoveFlag() const noexcept {
            return flags();
        }

        auto constexpr operator==(const Move& other) const noexcept -> bool {
            if(this == &other) return true;
            return value == other.value;
        }
    private:
        u16 value;
    };
}