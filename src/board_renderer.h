/**
* @author Steven Goldade
* @date 10/20/2023
*/
#pragma once
#include "tileset.h"
#include <chess/board.h>
#include <nespp/metatile.h>
#include <nespp/ppu.h>
#include <new>

using namespace nespp;
using namespace chess;

class BoardRenderer {
public:
    constexpr BoardRenderer(bool black_on_bottom, u8 metatile_x, u8 metatile_y) :black_on_bottom(black_on_bottom), board_metatile_x(metatile_x), board_metatile_y(metatile_y) {}
    
    auto constexpr render_full(const Board& board) const noexcept -> void {
        render_pieces(board);
        render_border();
    }
    auto constexpr render_move(const Board& board, const Move& move) const noexcept -> void {
        nespp::Vector<Square, 4> rerender_squares;

        auto const from_square = move.from_square();
        if(!from_square.is_valid()) {
            Error::fatal_error("Invalid FROM square in render", 29);
        }
        auto const to_square = move.to_square();
        if(!to_square.is_valid()) {
            Error::fatal_error("Invalid TO square in render", 27);
        }

        rerender_squares.push_back(from_square);
        rerender_squares.push_back(to_square);
        if(move.is_en_passant())
            rerender_squares.push_back(move.en_passant_square());
        if(move.is_king_side_castle()) {
            if(move.from_square() == Square::E1) {
                rerender_squares.push_back(Square::F1);
                rerender_squares.push_back(Square::H1);
            } else {
                rerender_squares.push_back(Square::F8);
                rerender_squares.push_back(Square::H8);
            }
        }
        if(move.is_queen_side_castle()) {
            if(move.from_square() == Square::E1) {
                rerender_squares.push_back(Square::A1);
                rerender_squares.push_back(Square::D1);
            } else {
                rerender_squares.push_back(Square::A8);
                rerender_squares.push_back(Square::D8);
            }
        }

        for(auto & square : rerender_squares) {
            render_piece(BufferedPpu::nametable_0, board.piece_at(square));
        }
    }

    auto constexpr set_black_on_bottom(const bool black_on_bottom) noexcept -> void {
        this->black_on_bottom = black_on_bottom;
    }

    auto constexpr set_metatile_x(const u8 metatile_x) noexcept -> void {
        board_metatile_x = metatile_x;
    }

    auto constexpr set_metatile_y(const u8 metatile_y) noexcept -> void {
        board_metatile_x = metatile_y;
    }
    
    auto constexpr hide_square(const Square& square) const noexcept -> void {
        render_piece(BufferedPpu::nametable_0, Piece(PieceType::NONE, square));
    }
    
    auto constexpr show_square(const Board& board, const Square& square) const noexcept -> void {
        render_piece(BufferedPpu::nametable_0, board.piece_at(square));
    }
    
    [[nodiscard]] auto constexpr square_metatile_x(const Square& square) const noexcept -> u8 {
        return board_metatile_x + (black_on_bottom ? 7-square.x() : square.x());
    }
    
    [[nodiscard]] auto constexpr square_top_y(const Square& square) const noexcept -> u8 {
        return square_metatile_y(square) * 16 - 1;
    }
    
    [[nodiscard]] auto constexpr square_bottom_y(const Square& square) const noexcept -> u8 {
        return square_top_y(square) + 15;
    }
    
    [[nodiscard]] auto constexpr square_metatile_y(const Square& square) const noexcept -> u8 {
        return board_metatile_y + (black_on_bottom ? square.y() : 7-square.y());
    }
    
    [[nodiscard]] auto constexpr square_left_x(const Square& square) const noexcept -> u8 {
        return square_metatile_x(square) * 16;
    }
    
    [[nodiscard]] auto constexpr square_right_x(const Square& square) const noexcept -> u8 {
        return square_left_x(square) + 15;
    }

private:
    bool black_on_bottom;
    u8 board_metatile_x;
    u8 board_metatile_y;
    
    static constexpr Metatile PIECES[13] = {
        {Tileset0::PALETTE_3, Tileset0::PALETTE_3, Tileset0::PALETTE_3, Tileset0::PALETTE_3},
        {Tileset0::WHITE_PAWN},
        {Tileset0::WHITE_KNIGHT},
        {Tileset0::WHITE_BISHOP},
        {Tileset0::WHITE_ROOK},
        {Tileset0::WHITE_QUEEN},
        {Tileset0::WHITE_KING},
        {Tileset0::BLACK_PAWN},
        {Tileset0::BLACK_KNIGHT},
        {Tileset0::BLACK_BISHOP},
        {Tileset0::BLACK_ROOK},
        {Tileset0::BLACK_QUEEN},
        {Tileset0::BLACK_KING},
    };
    
    enum Border {
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        LEFT,
        RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT
    };
    static constexpr u8 BORDER[8] = {
        Tileset0::BORDER_TOP_LEFT,
        Tileset0::BORDER_TOP_CENTER,
        Tileset0::BORDER_TOP_RIGHT,
        Tileset0::BORDER_LEFT,
        Tileset0::BORDER_RIGHT,
        Tileset0::BORDER_BOTTOM_LEFT,
        Tileset0::BORDER_BOTTOM_CENTER,
        Tileset0::BORDER_BOTTOM_RIGHT
    };
    
    static constexpr u8 FILE_LABELS[8] = {'A','B','C','D','E','F','G','H'};
    static constexpr u8 RANK_LABELS[8] = {'1','2','3','4','5','6','7','8'};
    
    template <VramAccessor T>
    auto constexpr render_piece(const T& vram_accessor, const Piece& piece) const noexcept -> void {
        auto & square = piece.square();
        const u8 metatile_x = square_metatile_x(square);
        const u8 metatile_y = square_metatile_y(square);
        const u8 tile_x = metatile_x * 2;
        const u8 tile_y = metatile_y * 2;
        PIECES[piece.piece_type()].write_to(vram_accessor, tile_x, tile_y);
    }
    
    auto constexpr render_pieces(const Board& board) const noexcept -> void {
        auto attribute_table = Ppu::attribute_table_0.cpu_copy();
        attribute_table.read();
    
        for(u8 square_index = 0; square_index < 64; square_index++) {
            auto const square = Square(square_index, false);
            auto const piece = board.piece_at(square);
        
            const u8 metatile_x = square_metatile_x(square);
            const u8 metatile_y = square_metatile_y(square);
            
            const u8 attribute_x = metatile_x / 2;
            const u8 attribute_sub_x = metatile_x % 2;
            const u8 attribute_y = metatile_y / 2;
            const u8 attribute_sub_y = metatile_y % 2;
            const u8 attribute_index = attribute_y * 8 + attribute_x;
        
            attribute_table.value[attribute_index].set(attribute_sub_x, attribute_sub_y, square.color() != SquareColor::WHITE);
            render_piece(Ppu::nametable_0, piece);
        }
        attribute_table.write();
    }
    auto constexpr render_border() const noexcept -> void {
        const u8 border_left_x = board_metatile_x*2 - 1;
        const u8 border_top_y = board_metatile_y*2 - 1;
        const u8 border_right_x = border_left_x + 17;
        const u8 border_bottom_y = border_top_y + 17;

        Ppu::nametable_0.write_partial(&BORDER[TOP_LEFT], 1, border_left_x, border_top_y);
        Ppu::nametable_0.write_partial(&BORDER[BOTTOM_LEFT], 1, border_left_x, border_bottom_y);
        for(auto i=0; i<8; ++i) {
            const u8 j = i*2 + 1;
            const u8 k = j+1;

            Ppu::nametable_0.write_partial(&BORDER[TOP_CENTER], 1, border_left_x + j, border_top_y);
            Ppu::nametable_0.write_partial(&BORDER[TOP_CENTER], 1, border_left_x + k, border_top_y);
            Ppu::nametable_0.write_partial(&BORDER[BOTTOM_CENTER], 1, border_left_x + j, border_bottom_y);
            Ppu::nametable_0.write_partial(&BORDER[BOTTOM_CENTER], 1, border_left_x + k, border_bottom_y);
            Ppu::nametable_0.write_partial(&FILE_LABELS[black_on_bottom ? 7-i : i], 1, border_left_x + j, border_bottom_y + 1);
            Ppu::nametable_0.write_partial(&BORDER[LEFT], 1, border_left_x, border_top_y + j);
            Ppu::nametable_0.write_partial(&BORDER[LEFT], 1, border_left_x, border_top_y + k);
            Ppu::nametable_0.write_partial(&RANK_LABELS[black_on_bottom ? i : 7-i], 1, border_left_x - 1, border_top_y + j);
            Ppu::nametable_0.write_partial(&BORDER[RIGHT], 1, border_right_x, border_top_y + j);
            Ppu::nametable_0.write_partial(&BORDER[RIGHT], 1, border_right_x, border_top_y + k);
        }
        Ppu::nametable_0.write_partial(&BORDER[TOP_RIGHT], 1, border_right_x, border_top_y);
        Ppu::nametable_0.write_partial(&BORDER[BOTTOM_RIGHT], 1, border_right_x, border_bottom_y);
    }
};