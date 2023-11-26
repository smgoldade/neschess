/**
 * @author Steven Goldade
 * @date 11/3/2023
 */
#pragma once
#include "ppu.h"
#include "types.h"

namespace nespp {
    auto constexpr tile_top_left(const u8 value) noexcept -> u8 {
        return value;
    }

    auto constexpr tile_top_right(const u8 value) noexcept -> u8 {
        return value+1;
    }

    auto constexpr tile_bottom_left(const u8 value) noexcept -> u8 {
        return value+0x10;
    }

    auto constexpr tile_bottom_right(const u8 value) noexcept -> u8 {
        return value+0x11;
    }

    struct Metatile {
        union {
            struct {
                u8 top_left;
                u8 top_right;
            };
            u8 top[2];
        };
        union {
            struct {
                u8 bottom_left;
                u8 bottom_right;
            };
            u8 bottom[2];
        };
        
        constexpr Metatile(const u8 source) : top_left(tile_top_left(source)), top_right(tile_top_right(source)), bottom_left(tile_bottom_left(source)), bottom_right(tile_bottom_right(source)) {}
        constexpr Metatile(const u8 _top_left, const u8 _top_right, const u8 _bottom_left, const u8 _bottom_right) : top_left(_top_left), top_right(_top_right), bottom_left(_bottom_left), bottom_right(_bottom_right) {}
    
        template <VramAccessor T>
        auto constexpr write_to(const T& vram_accessor, const u8 x, const u8 y) const noexcept -> void {
            vram_accessor.write_partial(top, 2, x, y);
            vram_accessor.write_partial(bottom, 2, x, y+1);
        }
    };
}
