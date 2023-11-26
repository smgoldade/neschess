/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include <nespp/types.h>
#include "side.h"
#include "square.h"

namespace chess {
    // a representation of a standard "bitboard" but done byte by byte
    struct Bitboard {
        explicit constexpr Bitboard(const u64 raw_bitboard) noexcept : board() {
            board[0] = raw_bitboard & 0xFF;
            board[1] = (raw_bitboard >> 8 * 1) & 0xFF;
            board[2] = (raw_bitboard >> 8 * 2) & 0xFF;
            board[3] = (raw_bitboard >> 8 * 3) & 0xFF;
            board[4] = (raw_bitboard >> 8 * 4) & 0xFF;
            board[5] = (raw_bitboard >> 8 * 5) & 0xFF;
            board[6] = (raw_bitboard >> 8 * 6) & 0xFF;
            board[7] = (raw_bitboard >> 8 * 7) & 0xFF;
        }

        constexpr Bitboard(const std::initializer_list<u8>& init) noexcept : board() {
            auto it = init.begin();
            for(size_t i = 0; i < init.size(); ++i)
                board[i] = it[i];
        }

        [[nodiscard]] auto constexpr is_set(const Square& square) const noexcept -> bool {
            return (board[square.y()] & (1 << square.x()));
        }

        auto constexpr set(const Square& square) noexcept -> void {
            board[square.y()] |= (1 << square.x());
        }

        auto constexpr clear(const Square& square) noexcept -> void {
            board[square.y()] &= ~(1 << square.x());
        }

        auto constexpr try_grab(const Square& square) noexcept -> bool {
            if(!is_set(square)) return false;
            clear(square);
            return true;
        }

        auto constexpr operator~() const noexcept -> Bitboard {
            return {
                static_cast<u8>(~board[0]),
                static_cast<u8>(~board[1]),
                static_cast<u8>(~board[2]),
                static_cast<u8>(~board[3]),
                static_cast<u8>(~board[4]),
                static_cast<u8>(~board[5]),
                static_cast<u8>(~board[6]),
                static_cast<u8>(~board[7]),
            };
        }

        auto constexpr operator&(const Bitboard& other) const noexcept -> Bitboard {
            return {
                static_cast<u8>(board[0] & other.board[0]),
                static_cast<u8>(board[1] & other.board[1]),
                static_cast<u8>(board[2] & other.board[2]),
                static_cast<u8>(board[3] & other.board[3]),
                static_cast<u8>(board[4] & other.board[4]),
                static_cast<u8>(board[5] & other.board[5]),
                static_cast<u8>(board[6] & other.board[6]),
                static_cast<u8>(board[7] & other.board[7]),
            };
        }

        auto constexpr operator&=(const Bitboard& other) noexcept -> Bitboard& {
            board[0] &= other.board[0];
            board[1] &= other.board[1];
            board[2] &= other.board[2];
            board[3] &= other.board[3];
            board[4] &= other.board[4];
            board[5] &= other.board[5];
            board[6] &= other.board[6];
            board[7] &= other.board[7];
            return *this;
        }

        auto constexpr operator|(const Bitboard& other) const noexcept -> Bitboard {
            return {
                static_cast<u8>(board[0] | other.board[0]),
                static_cast<u8>(board[1] | other.board[1]),
                static_cast<u8>(board[2] | other.board[2]),
                static_cast<u8>(board[3] | other.board[3]),
                static_cast<u8>(board[4] | other.board[4]),
                static_cast<u8>(board[5] | other.board[5]),
                static_cast<u8>(board[6] | other.board[6]),
                static_cast<u8>(board[7] | other.board[7]),
            };
        }

        auto constexpr operator|=(const Bitboard& other) noexcept -> Bitboard& {
            board[0] |= other.board[0];
            board[1] |= other.board[1];
            board[2] |= other.board[2];
            board[3] |= other.board[3];
            board[4] |= other.board[4];
            board[5] |= other.board[5];
            board[6] |= other.board[6];
            board[7] |= other.board[7];
            return *this;
        }

        auto constexpr operator^(const Bitboard& other) const noexcept -> Bitboard {
            return {
                static_cast<u8>(board[0] ^ other.board[0]),
                static_cast<u8>(board[1] ^ other.board[1]),
                static_cast<u8>(board[2] ^ other.board[2]),
                static_cast<u8>(board[3] ^ other.board[3]),
                static_cast<u8>(board[4] ^ other.board[4]),
                static_cast<u8>(board[5] ^ other.board[5]),
                static_cast<u8>(board[6] ^ other.board[6]),
                static_cast<u8>(board[7] ^ other.board[7]),
            };
        }

        auto constexpr operator^=(const Bitboard& other) noexcept -> Bitboard& {
            board[0] ^= other.board[0];
            board[1] ^= other.board[1];
            board[2] ^= other.board[2];
            board[3] ^= other.board[3];
            board[4] ^= other.board[4];
            board[5] ^= other.board[5];
            board[6] ^= other.board[6];
            board[7] ^= other.board[7];
            return *this;
        }
    private:
        u8 board[8];
    };
}// namespace chess