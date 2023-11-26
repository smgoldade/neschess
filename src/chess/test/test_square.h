/**
* @author Steven Goldade
* @date 11/12/2023
*/
#include <chess/square.h>

using namespace chess;

auto constexpr direction() -> bool {
    static_assert(!is_diagonal(Direction::NORTH));
    static_assert(is_diagonal(Direction::NORTHEAST));
    static_assert(!is_diagonal(Direction::EAST));
    static_assert(is_diagonal(Direction::SOUTHEAST));
    static_assert(!is_diagonal(Direction::SOUTH));
    static_assert(is_diagonal(Direction::SOUTHWEST));
    static_assert(!is_diagonal(Direction::WEST));
    static_assert(is_diagonal(Direction::NORTHWEST));
    
    static_assert(is_cardinal(Direction::NORTH));
    static_assert(!is_cardinal(Direction::NORTHEAST));
    static_assert(is_cardinal(Direction::EAST));
    static_assert(!is_cardinal(Direction::SOUTHEAST));
    static_assert(is_cardinal(Direction::SOUTH));
    static_assert(!is_cardinal(Direction::SOUTHWEST));
    static_assert(is_cardinal(Direction::WEST));
    static_assert(!is_cardinal(Direction::NORTHWEST));
    
    static_assert(opposite_direction(Direction::NORTH) == Direction::SOUTH);
    static_assert(opposite_direction(Direction::NORTHEAST) == Direction::SOUTHWEST);
    static_assert(opposite_direction(Direction::EAST) == Direction::WEST);
    static_assert(opposite_direction(Direction::SOUTHEAST) == Direction::NORTHWEST);
    static_assert(opposite_direction(Direction::SOUTH) == Direction::NORTH);
    static_assert(opposite_direction(Direction::SOUTHWEST) == Direction::NORTHEAST);
    static_assert(opposite_direction(Direction::WEST) == Direction::EAST);
    static_assert(opposite_direction(Direction::NORTHWEST) == Direction::SOUTHEAST);
    
    return true;
}

auto constexpr square() -> bool {
    static_assert(Square() == Square::INVALID, "Default Square = INVALID");
    static_assert(Square(0x11) == Square::B2, "Square(0x11) == B2 (0x88)");
    static_assert(Square(0x11, false) == Square::B3, "Square(0x11, false) = B3 (8x8)");
    static_assert(Square(Square::C7) == Square::C7, "Square(C7) = C7");
    static_assert(Square(File::G, Rank::_4) == Square::G4, "Square(G, 4) = G4");
    static_assert(Square(File::INVALID, Rank::_4) == Square::INVALID, "Square(INVALID, 4) = INVALID");
    static_assert(Square(File::G, Rank::INVALID) == Square::INVALID, "Square(G, INVALID) = INVALID");
    
    static_assert(static_cast<u8>(Square(Square::F5)) == 0x45, "(u8)(Square(F5)) = 0x45");
    static_assert(Square(Square::F5).as_8x8_square_index() == 0x25, "Square(F5).as8x8 = 0x25 (37)");
    static_assert(Square(Square::H8).is_valid(), "Square(H8).is_valid");
    static_assert(!Square(Square::INVALID).is_valid(), "!Square(INVALID).is_valid");
    static_assert(!Square(0x88).is_valid(), "!Square(0x88).is_valid");
    static_assert(!Square(0x87).is_valid(), "!Square(0x87).is_valid");
    static_assert(!Square(0x78).is_valid(), "!Square(0x78).is_valid");
    
    static_assert(Square(Square::D7).file() == File::D, "Square(D7).file = D");
    static_assert(Square(0x88).file() == File::INVALID, "Square(0x88).file = INVALID");
    static_assert(Square(Square::A3).x() == 0, "Square(A3).x = 0");
    static_assert(Square(Square::H3).x() == 7, "Square(H3).x = 7");
    static_assert(Square(0x98).x() == 0xFF, "Square(0x98).x = FF");
    static_assert(Square(Square::D3).rank() == Rank::_3, "Square(D3).rank = 3");
    static_assert(Square(Square::B1).y() == 0, "Square(B1).y = 0");
    static_assert(Square(Square::G8).y() == 7, "Square(G8).y = 7");
    static_assert(Square(0x98).y() == 0xFF, "Square(0x98).y = FF");
    static_assert(Square(0x88).rank() == Rank::INVALID, "Square(0x88).rank = INVALID");
    
    static_assert(Square(Square::A1).color() == SquareColor::BLACK, "A1.color = BLACK");
    static_assert(Square(Square::A2).color() == SquareColor::WHITE, "A2.color = WHITE");
    static_assert(Square(Square::B1).color() == SquareColor::WHITE, "B1.color = WHITE");
    static_assert(Square(Square::B2).color() == SquareColor::BLACK, "B1.color = BLACK");
    
    static_assert(Square(Square::E2).north() == Square::E3, "E2.north = E3");
    static_assert(Square(Square::E8).north() == Square::INVALID, "E8.north = INVALID");
    static_assert(Square(0x0F).north() == Square::INVALID, "0F.north = INVALID");
    static_assert(Square(Square::E2).northeast() == Square::F3, "E2.northeast = F3");
    static_assert(Square(Square::E8).northeast() == Square::INVALID, "E8.northeast = INVALID");
    static_assert(Square(Square::H7).northeast() == Square::INVALID, "H7.northeast = INVALID");
    static_assert(Square(0x80).northeast() == Square::INVALID, "80.northeast = INVALID");
    static_assert(Square(Square::E2).east() == Square::F2, "E2.east = F2");
    static_assert(Square(Square::H2).east() == Square::INVALID, "H2.east = INVALID");
    static_assert(Square(0x0F).east() == Square::INVALID, "0F.east = INVALID");
    static_assert(Square(Square::E2).southeast() == Square::F1, "E2.southeast = F1");
    static_assert(Square(Square::H2).southeast() == Square::INVALID, "H2.southeast = INVALID");
    static_assert(Square(0x78).southeast() == Square::INVALID, "78.southeast = INVALID");
    static_assert(Square(Square::E2).south() == Square::E1, "E2.south = F1");
    static_assert(Square(Square::H1).south() == Square::INVALID, "H1.south = INVALID");
    static_assert(Square(0x78).south() == Square::INVALID, "78.south = INVALID");
    static_assert(Square(Square::E2).southwest() == Square::D1, "E2.southwest = D1");
    static_assert(Square(Square::H1).southwest() == Square::INVALID, "H1.southwest = INVALID");
    static_assert(Square(0x78).southwest() == Square::INVALID, "78.southwest = INVALID");
    static_assert(Square(Square::E2).west() == Square::D2, "E2.west = D2");
    static_assert(Square(Square::A1).west() == Square::INVALID, "A1.west = INVALID");
    static_assert(Square(0x78).west() == Square::INVALID, "78.west = INVALID");
    static_assert(Square(Square::E2).northwest() == Square::D3, "E2.west = D3");
    static_assert(Square(Square::A1).northwest() == Square::INVALID, "A1.northwest = INVALID");
    static_assert(Square(0x78).northwest() == Square::INVALID, "78.northwest = INVALID");
    
    static_assert(Square::direction(Square::E2, Square::E3) == Direction::NORTH, "E2.dir E3 = NORTH");
    static_assert(Square::direction(Square::E2, Square::F3) == Direction::NORTHEAST, "E2.dir F3 = NORTHEAST");
    static_assert(Square::direction(Square::E2, Square::F2) == Direction::EAST, "E2.dir F2 = EAST");
    static_assert(Square::direction(Square::E2, Square::F1) == Direction::SOUTHEAST, "E2.dir F1 = SOUTHEAST");
    static_assert(Square::direction(Square::E2, Square::E1) == Direction::SOUTH, "E2.dir E1 = SOUTH");
    static_assert(Square::direction(Square::E2, Square::D1) == Direction::SOUTHWEST, "E2.dir D1 = SOUTHWEST");
    static_assert(Square::direction(Square::E2, Square::D2) == Direction::WEST, "E2.dir D2 = WEST");
    static_assert(Square::direction(Square::E2, Square::D3) == Direction::NORTHWEST, "E2.dir D3 = NORTHWEST");
    static_assert(Square::direction(Square::E2, Square::A8) == Direction::NORTHWEST, "E2.dir A8 = NORTHWEST");
    static_assert(Square::direction(Square::E2, Square::H8) == Direction::NORTHEAST, "E2.dir H8 = NORTHEAST");
    static_assert(Square::direction(Square::E2, Square::H3) == Direction::NORTHEAST, "E2.dir H3 = NORTHEAST");
    static_assert(Square::direction(Square::E2, Square::H1) == Direction::SOUTHEAST, "E2.dir H1 = SOUTHEAST");
    static_assert(Square::direction(Square::E2, Square::A1) == Direction::SOUTHWEST, "E2.dir A1 = SOUTHWEST");

    static_assert(Square(Square::E2).direction(Square::E3) == Direction::NORTH, "E2.dir E3 = NORTH");
    static_assert(Square(Square::E2).direction(Square::F3) == Direction::NORTHEAST, "E2.dir F3 = NORTHEAST");
    static_assert(Square(Square::E2).direction(Square::F2) == Direction::EAST, "E2.dir F2 = EAST");
    static_assert(Square(Square::E2).direction(Square::F1) == Direction::SOUTHEAST, "E2.dir F1 = SOUTHEAST");
    static_assert(Square(Square::E2).direction(Square::E1) == Direction::SOUTH, "E2.dir E1 = SOUTH");
    static_assert(Square(Square::E2).direction(Square::D1) == Direction::SOUTHWEST, "E2.dir D1 = SOUTHWEST");
    static_assert(Square(Square::E2).direction(Square::D2) == Direction::WEST, "E2.dir D2 = WEST");
    static_assert(Square(Square::E2).direction(Square::D3) == Direction::NORTHWEST, "E2.dir D3 = NORTHWEST");
    
    static_assert(Square(Square::E2).ray(Direction::NORTH) == Square::E3);
    static_assert(Square(Square::E2).ray(Direction::NORTHEAST) == Square::F3);
    static_assert(Square(Square::E2).ray(Direction::EAST) == Square::F2);
    static_assert(Square(Square::E2).ray(Direction::SOUTHEAST) == Square::F1);
    static_assert(Square(Square::E2).ray(Direction::SOUTH) == Square::E1);
    static_assert(Square(Square::E2).ray(Direction::SOUTHWEST) == Square::D1);
    static_assert(Square(Square::E2).ray(Direction::WEST) == Square::D2);
    static_assert(Square(Square::E2).ray(Direction::NORTHWEST) == Square::D3);
    
    static_assert(Square(Square::E2).manhattan_distance(Square::E1) == 1);
    static_assert(Square(Square::E2).manhattan_distance(Square::E2) == 0);
    static_assert(Square(Square::E2).manhattan_distance(Square::E4) == 2);
    static_assert(Square(Square::E2).manhattan_distance(Square::E8) == 6);
    static_assert(Square(Square::E2).manhattan_distance(Square::F3) == 2);
    static_assert(Square(Square::A1).manhattan_distance(Square::H8) == 14);
    static_assert(Square(Square::H8).manhattan_distance(Square::A1) == 14);
    
    return true;
}

auto constexpr test_square() -> bool {
    static_assert(direction(), "Direction");
    static_assert(square(), "Square");
    return true;
}