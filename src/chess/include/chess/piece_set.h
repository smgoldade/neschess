/**
 * @author Steven Goldade
 * @date 11/25/2023
 */
#pragma once
#include "piece.h"
#include <nespp/error.h>
#include <nespp/vector.h>

namespace chess {
    struct PieceSet {
        using iterator = const Piece*;
        using const_iterator = const Piece*;

        explicit constexpr PieceSet(bool black, bool invalid=false) noexcept : pieces {
            {black ? PieceType::BLACK_PAWN : PieceType::WHITE_PAWN, invalid ? Square::INVALID : black ? Square::A7 : Square::A2},
            {black ? PieceType::BLACK_PAWN : PieceType::WHITE_PAWN, invalid ? Square::INVALID : black ? Square::B7 : Square::B2},
            {black ? PieceType::BLACK_PAWN : PieceType::WHITE_PAWN, invalid ? Square::INVALID : black ? Square::C7 : Square::C2},
            {black ? PieceType::BLACK_PAWN : PieceType::WHITE_PAWN, invalid ? Square::INVALID : black ? Square::D7 : Square::D2},
            {black ? PieceType::BLACK_PAWN : PieceType::WHITE_PAWN, invalid ? Square::INVALID : black ? Square::E7 : Square::E2},
            {black ? PieceType::BLACK_PAWN : PieceType::WHITE_PAWN, invalid ? Square::INVALID : black ? Square::F7 : Square::F2},
            {black ? PieceType::BLACK_PAWN : PieceType::WHITE_PAWN, invalid ? Square::INVALID : black ? Square::G7 : Square::G2},
            {black ? PieceType::BLACK_PAWN : PieceType::WHITE_PAWN, invalid ? Square::INVALID : black ? Square::H7 : Square::H2},
            {black ? PieceType::BLACK_ROOK : PieceType::WHITE_ROOK, invalid ? Square::INVALID : black ? Square::A8 : Square::A1},
            {black ? PieceType::BLACK_KNIGHT : PieceType::WHITE_KNIGHT, invalid ? Square::INVALID : black ? Square::B8 : Square::B1},
            {black ? PieceType::BLACK_BISHOP : PieceType::WHITE_BISHOP, invalid ? Square::INVALID : black ? Square::C8 : Square::C1},
            {black ? PieceType::BLACK_QUEEN : PieceType::WHITE_QUEEN, invalid ? Square::INVALID : black ? Square::D8 : Square::D1},
            {black ? PieceType::BLACK_KING : PieceType::WHITE_KING, invalid ? Square::INVALID : black ? Square::E8 : Square::E1},
            {black ? PieceType::BLACK_BISHOP : PieceType::WHITE_BISHOP, invalid ? Square::INVALID : black ? Square::F8 : Square::F1},
            {black ? PieceType::BLACK_KNIGHT : PieceType::WHITE_KNIGHT, invalid ? Square::INVALID : black ? Square::G8 : Square::G1},
            {black ? PieceType::BLACK_ROOK : PieceType::WHITE_ROOK, invalid ? Square::INVALID : black ? Square::H8 : Square::H1},
        }, cached_index(0), counts {0, static_cast<u8>(invalid ? 0 : 2), static_cast<u8>(invalid ? 0 : 2), static_cast<u8>(invalid ? 0 : 2), static_cast<u8>(invalid ? 0 : 2), static_cast<u8>(invalid ? 0 : 1), static_cast<u8>(invalid ? 0 : 1)}, piece_count(invalid ? 0 : 16) {}

        auto constexpr NONREENTRANT cleanup() {
            // Moves valid pieces into the array
            for(u8 i=piece_count; i<16; ++i) {
                auto & piece = pieces[i];
                if(piece.square().is_valid()) {
                    auto swap_piece = pieces[piece_count];
                    pieces[piece_count] = piece;
                    piece_count++;
                    piece = swap_piece;
                }
            }

            // Moves invalid pieces to the back of the array
            for(u8 i=0; i<piece_count; ++i) {
                auto & piece = pieces[i];
                if(!piece.square().is_valid()) {
                    auto swap_piece = pieces[piece_count-1];
                    pieces[piece_count-1] = piece;
                    piece_count--;
                    piece = swap_piece;
                }
            }

            counts[1] = 0;
            counts[2] = 0;
            counts[3] = 0;
            counts[4] = 0;
            counts[5] = 0;
            counts[6] = 0;
            for(u8 i=0; i<piece_count; ++i) {
                auto & piece = pieces[i];
                counts[static_cast<u8>(piece.piece_type().basic_piece_type())]++;
            }
        }

        struct ReferencedPiece {
            Piece& piece;

            constexpr ReferencedPiece(Piece& piece, const u8 index, PieceSet* parent) : piece(piece), index(index), need_cleanup(false), parent(parent) {}

            auto constexpr mark_cleanup() noexcept -> void {
                need_cleanup = true;
            }

            constexpr ~ReferencedPiece() {
                if(!parent) return;

                parent->cached_index = index;
                if(need_cleanup)
                    parent->cleanup();
            }
        private:
            u8 index;
            bool need_cleanup;
            PieceSet* parent;
        };

        auto constexpr grab_piece(const Piece& piece) -> ReferencedPiece {
            if(piece == pieces[cached_index]) return {pieces[cached_index], cached_index, this};
            for(u8 i=0; i<piece_count; ++i) {
                auto & my_piece = pieces[i];
                if(my_piece == piece) return {my_piece, i, this};
            }
            nespp::Error::fatal_error("Illegal piece grab", 18);
            return { pieces[0], 0, nullptr};
        }

        auto constexpr grab_captured_piece(const Piece& piece) -> ReferencedPiece {
            for(u8 i=piece_count; i<16; ++i) {
                auto & my_piece = pieces[i];
                if(my_piece == piece) return {my_piece, i, this};
            }
            nespp::Error::fatal_error("Illegal captured piece grab", 27);
            return { pieces[0], 0, nullptr};
        }

        auto constexpr grab_invalid(const PieceType piece_type) -> ReferencedPiece {
            for(u8 i=piece_count; i<16; ++i) {
                auto & my_piece = pieces[i];
                if(my_piece.piece_type() == piece_type) return {my_piece, i, this};
            }
            if(piece_type.basic_piece_type() != BasicPieceType::PAWN) {
                for(u8 i=piece_count; i<16; ++i) {
                    auto & my_piece = pieces[i];
                    if(my_piece.piece_type().basic_piece_type() == BasicPieceType::PAWN) {
                        my_piece.promote(piece_type.basic_piece_type());
                        return {my_piece, i, this};
                    }
                }
            }
            nespp::Error::fatal_error("Illegal invalid piece grab", 26);
            return { pieces[0], 0, nullptr};
        }

        [[nodiscard]] auto constexpr get_king() const noexcept -> const Piece& {
            for(u8 i=0; i<piece_count; ++i) {
                auto const & piece = pieces[i];
                if(piece.is_king()) return piece;
            }
            nespp::Error::fatal_error("Illegal position with no king", 29);
            return pieces[0];
        }

        [[nodiscard]] auto constexpr begin() const noexcept -> const_iterator {
            return pieces.begin();
        }

        auto constexpr begin() noexcept -> iterator {
            return pieces.begin();
        }

        [[nodiscard]] auto constexpr end() const noexcept -> const_iterator {
            return pieces.begin() + piece_count;
        }

        auto constexpr end() noexcept -> iterator {
            return pieces.begin() + piece_count;
        }
    private:
        nespp::Array<Piece, 16> pieces;
        u8 cached_index;
        u8 counts[7];
        u8 piece_count;
    };
}