// Author: Steven Goldade
#pragma once
#include <nespp/nesmath.h>
#include <nespp/types.h>
#include <nespp/vector.h>

namespace chess {
    enum class SquareColor : u8 {
        BLACK,
        WHITE
    };

    enum class Direction : u8 {
        NORTH,
        NORTHEAST,
        EAST,
        SOUTHEAST,
        SOUTH,
        SOUTHWEST,
        WEST,
        NORTHWEST
    };
    static constexpr nespp::Array<Direction, 8> DIRECTIONS = {Direction::NORTH, Direction::NORTHEAST, Direction::EAST, Direction::SOUTHEAST, Direction::SOUTH, Direction::SOUTHWEST, Direction::WEST, Direction::NORTHWEST};
    static constexpr nespp::Array<Direction, 4> DIAGONALS = {Direction::NORTHEAST, Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::NORTHWEST};
    static constexpr nespp::Array<Direction, 4> CARDINALS = {Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST};
    auto constexpr is_diagonal(const Direction direction) noexcept -> bool {
        switch(direction) {
            case Direction::NORTH:
            case Direction::EAST:
            case Direction::SOUTH:
            case Direction::WEST:
                return false;
            case Direction::NORTHEAST:
            case Direction::SOUTHEAST:
            case Direction::SOUTHWEST:
            case Direction::NORTHWEST:
                return true;
        }
    }
    auto constexpr is_cardinal(const Direction direction) noexcept -> bool {
        return !is_diagonal(direction);
    }
    auto constexpr opposite_direction(const Direction direction) noexcept -> Direction {
        switch(direction) {
            case Direction::NORTH:
                return Direction::SOUTH;
            case Direction::NORTHEAST:
                return Direction::SOUTHWEST;
            case Direction::EAST:
                return Direction::WEST;
            case Direction::SOUTHEAST:
                return Direction::NORTHWEST;
            case Direction::SOUTH:
                return Direction::NORTH;
            case Direction::SOUTHWEST:
                return Direction::NORTHEAST;
            case Direction::WEST:
                return Direction::EAST;
            case Direction::NORTHWEST:
                return Direction::SOUTHEAST;
        }
    }
    
    enum class File : u8 {
        INVALID = 0,
        A = 1,
        B = 2,
        C = 3,
        D = 4,
        E = 5,
        F = 6,
        G = 7,
        H = 8
    };

    enum class Rank : u8 {
        INVALID = 0,
        _1 = 1,
        _2 = 2,
        _3 = 3,
        _4 = 4,
        _5 = 5,
        _6 = 6,
        _7 = 7,
        _8 = 8
    };

    struct Square {
        enum Value : u8 {
            A1 = 0x00,B1 = 0x01,C1 = 0x02,D1 = 0x03,E1 = 0x04,F1 = 0x05,G1 = 0x06,H1 = 0x07,
            A2 = 0x10,B2 = 0x11,C2 = 0x12,D2 = 0x13,E2 = 0x14,F2 = 0x15,G2 = 0x16,H2 = 0x17,
            A3 = 0x20,B3 = 0x21,C3 = 0x22,D3 = 0x23,E3 = 0x24,F3 = 0x25,G3 = 0x26,H3 = 0x27,
            A4 = 0x30,B4 = 0x31,C4 = 0x32,D4 = 0x33,E4 = 0x34,F4 = 0x35,G4 = 0x36,H4 = 0x37,
            A5 = 0x40,B5 = 0x41,C5 = 0x42,D5 = 0x43,E5 = 0x44,F5 = 0x45,G5 = 0x46,H5 = 0x47,
            A6 = 0x50,B6 = 0x51,C6 = 0x52,D6 = 0x53,E6 = 0x54,F6 = 0x55,G6 = 0x56,H6 = 0x57,
            A7 = 0x60,B7 = 0x61,C7 = 0x62,D7 = 0x63,E7 = 0x64,F7 = 0x65,G7 = 0x66,H7 = 0x67,
            A8 = 0x70,B8 = 0x71,C8 = 0x72,D8 = 0x73,E8 = 0x74,F8 = 0x75,G8 = 0x76,H8 = 0x77,
            INVALID = 0xFF
        };

        constexpr Square() noexcept : value(INVALID) {}
        constexpr explicit Square(const u8 index, bool as88 = true) noexcept : value(as88 ? static_cast<Value>(index) : static_cast<Value>(index + (index & 0xF8))) {}
        constexpr Square(const Value value) noexcept : value(value) {} // NOLINT(*-explicit-constructor)
        constexpr Square(const File file, const Rank rank) noexcept {
            if(file == File::INVALID || rank == Rank::INVALID) {
                value = INVALID;
                return;
            }
            value = static_cast<Value>(((static_cast<u8>(rank)-1) << 4) + (static_cast<u8>(file)-1));
        }

        constexpr explicit operator Value() const noexcept { return value; }
        constexpr explicit operator u8() const noexcept { return static_cast<u8>(value); }
        constexpr explicit operator bool() const = delete;
        
        [[nodiscard]] auto constexpr as_8x8_square_index() const noexcept -> u8 {
            auto v88 = static_cast<u8>(value);
            return (v88 + (v88 & 0x07)) >> 1;
        }

        [[nodiscard]] auto constexpr is_valid() const noexcept -> bool {
            return !(value & 0x88);
        }

        constexpr explicit operator File() const noexcept {
            return file();
        }

        [[nodiscard]] auto constexpr file() const noexcept -> File {
            if(!is_valid()) return File::INVALID;
            return static_cast<File>((static_cast<u8>(value) & 0x7) + 1);
        }

        [[nodiscard]] auto constexpr x() const noexcept -> u8 {
            if(!is_valid()) return 255;
            return static_cast<u8>(value) & 0x7;
        }

        constexpr explicit operator Rank() const noexcept {
            return rank();
        }

        [[nodiscard]] auto constexpr rank() const noexcept -> Rank {
            if(!is_valid()) return Rank::INVALID;
            return static_cast<Rank>(y() + 1);
        }

        [[nodiscard]] auto constexpr y() const noexcept -> u8 {
            if(!is_valid()) return 255;
            return static_cast<u8>(value) >> 4;
        }

        constexpr explicit operator SquareColor() const noexcept {
            return color();
        }
        [[nodiscard]] auto constexpr color() const noexcept -> SquareColor {
            return static_cast<SquareColor>((static_cast<u8>(rank()) + static_cast<u8>(file())) % 2);
        }

        [[nodiscard]] auto constexpr north() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value + 0x10);
        }

        [[nodiscard]] auto constexpr northeast() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value + 0x11);
        }

        [[nodiscard]] auto constexpr east() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value + 0x01);
        }

        [[nodiscard]] auto constexpr southeast() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value - 0x0F);
        }

        [[nodiscard]] auto constexpr south() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value - 0x10);
        }

        [[nodiscard]] auto constexpr southwest() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value - 0x11);
        }

        [[nodiscard]] auto constexpr west() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value - 0x01);
        }

        [[nodiscard]] auto constexpr northwest() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value + 0x0F);
        }

        [[nodiscard]] auto constexpr knight_1() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value + 0x21);
        }

        [[nodiscard]] auto constexpr knight_2() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value + 0x12);
        }

        [[nodiscard]] auto constexpr knight_3() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value - 0x0E);
        }

        [[nodiscard]] auto constexpr knight_4() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value - 0x1F);
        }

        [[nodiscard]] auto constexpr knight_5() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value - 0x21);
        }

        [[nodiscard]] auto constexpr knight_6() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value - 0x12);
        }

        [[nodiscard]] auto constexpr knight_7() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value + 0x0E);
        }

        [[nodiscard]] auto constexpr knight_8() const noexcept -> Square {
            if(!is_valid()) return INVALID;
            return Square(value + 0x1F);
        }

        [[nodiscard]] auto static constexpr direction(const Square& from, const Square& to) noexcept -> Direction {
            if(to.value > from.value) {
                if(to.rank() == from.rank()) return Direction::EAST;
                if(to.file() == from.file()) return Direction::NORTH;
                if(to.file() > from.file()) return Direction::NORTHEAST;
                return Direction::NORTHWEST;
            } else {
                if(to.rank() == from.rank()) return Direction::WEST;
                if(to.file() == from.file()) return Direction::SOUTH;
                if(to.file() > from.file()) return Direction::SOUTHEAST;
                return Direction::SOUTHWEST;
            }
        }

        [[nodiscard]] auto constexpr direction(const Square& to) const noexcept -> Direction {
            return Square::direction(*this, to);
        }

        [[nodiscard]] auto constexpr ray(const Direction direction) const noexcept -> Square {
            switch(direction) {
                case Direction::NORTH:
                    return north();
                case Direction::NORTHEAST:
                    return northeast();
                case Direction::EAST:
                    return east();
                case Direction::SOUTHEAST:
                    return southeast();
                case Direction::SOUTH:
                    return south();
                case Direction::SOUTHWEST:
                    return southwest();
                case Direction::WEST:
                    return west();
                case Direction::NORTHWEST:
                    return northwest();
            }
        }

        [[nodiscard]] auto constexpr manhattan_distance(const Square& other) const noexcept -> u8 {
            if(!other.is_valid() || !is_valid()) return 255;
            return nespp::abs(x() - other.x()) + nespp::abs(y() - other.y());
        }

        auto constexpr operator==(const Square& other) const noexcept -> bool {
            if(this == &other) return true;
            if(!is_valid() && !other.is_valid()) return true;
            return value == other.value;
        }

        auto constexpr operator==(const Value& other) const noexcept -> bool {
            auto o = Square(other);
            if(!is_valid() && !o.is_valid()) return true;
            return value == o.value;
        }
    private:
        Value value;
    };
}