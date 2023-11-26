/**
* @author Steven Goldade
* @date 11/10/2023
*/
#pragma once
#include "ppu.h"
#include "types.h"

namespace nespp {
    class Metasprite {
    public:
        explicit constexpr Metasprite(const u8 index) : Metasprite(index, 8, 8) {}
        constexpr Metasprite(const u8 index, const u8 x_offset, const u8 y_offset) : x_offset(x_offset), y_offset(y_offset), top_left_sprite(Ppu::sprites[index]), top_right_sprite(Ppu::sprites[index + 1]), bottom_left_sprite(Ppu::sprites[index + 2]), bottom_right_sprite(Ppu::sprites[index + 3]) {}

        auto constexpr set_tile(const u8 tile_index) noexcept -> void {
            auto constexpr set_sprite = [&](PpuSprite& sprite, const u8 tile_number) {
                sprite.tile_number = tile_number;
                sprite.horizontal_flip = false;
                sprite.vertical_flip = false;
            };

            set_sprite(top_left_sprite, tile_top_left(tile_index));
            set_sprite(top_right_sprite, tile_top_right(tile_index));
            set_sprite(bottom_left_sprite, tile_bottom_left(tile_index));
            set_sprite(bottom_right_sprite, tile_bottom_right(tile_index));
        }

        auto constexpr set_reflected_tile(const u8 tile_index) noexcept -> void {
            auto constexpr set_sprite = [&](PpuSprite& sprite, const u8 tile_number, const bool horizontal = false, const bool vertical = false) {
                sprite.tile_number = tile_number;
                sprite.horizontal_flip = horizontal;
                sprite.vertical_flip = vertical;
            };

            set_sprite(top_left_sprite, tile_top_left(tile_index));
            set_sprite(top_right_sprite, tile_top_left(tile_index), true);
            set_sprite(bottom_left_sprite, tile_top_left(tile_index), false, true);
            set_sprite(bottom_right_sprite, tile_top_left(tile_index), true, true);
        }

        auto constexpr set_coordinates(const u8 x, const u8 y) noexcept -> void {
            top_left_sprite.x = x;
            top_left_sprite.y = y;
            top_right_sprite.x = x + x_offset;
            top_right_sprite.y = y;
            bottom_left_sprite.x = x;
            bottom_left_sprite.y = y + y_offset;
            bottom_right_sprite.x = x + x_offset;
            bottom_right_sprite.y = y + y_offset;
        }

        auto constexpr set_behind_background(const bool behind_background) noexcept -> void {
            top_left_sprite.behind_background = behind_background;
            top_right_sprite.behind_background = behind_background;
            bottom_left_sprite.behind_background = behind_background;
            bottom_right_sprite.behind_background = behind_background;
        }

        auto constexpr set_palette(const u8 palette) noexcept -> void {
            top_left_sprite.palette = palette;
            top_right_sprite.palette = palette;
            bottom_left_sprite.palette = palette;
            bottom_right_sprite.palette = palette;
        }

        auto constexpr hide() noexcept -> void {
            top_left_sprite.hide();
            top_right_sprite.hide();
            bottom_left_sprite.hide();
            bottom_right_sprite.hide();
        }

    private:
        u8 x_offset;
        u8 y_offset;

        PpuSprite& top_left_sprite;
        PpuSprite& top_right_sprite;
        PpuSprite& bottom_left_sprite;
        PpuSprite& bottom_right_sprite;
    };
}// namespace nespp
