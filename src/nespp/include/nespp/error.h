/**
* @author Steven Goldade
* @date 11/19/2023
*/
#pragma once
#include "ppu.h"

namespace nespp::Error {
    auto constexpr fatal_error(const char* msg, u8 size) noexcept -> void {
        BufferedPpu::off();
        if !consteval { Ppu::wait(); }
        BufferedPpu::control.nametable = 0;
        BufferedPpu::control.background_pattern_table = 0;

        u8 clean[] = {0x00, 0x00, 0x00, 0x00};
        for(u16 i = 0; i<0x400; i+=4)
            Ppu::nametable_0.write_partial(clean, 4, i);
        Ppu::clear_sprites();
        Ppu::nametable_0.write_partial(reinterpret_cast<const u8*>(msg), size, 16 - size/2, 10);

        Ppu::background_palette.write({
            Color::DARK_BLUE,
            {Color::WHITE, Color::WHITE, Color::WHITE},
            Color::DARK_BLUE,
            {Color::WHITE, Color::WHITE, Color::WHITE},
            Color::DARK_BLUE,
            {Color::WHITE, Color::WHITE, Color::WHITE},
            Color::DARK_BLUE,
            {Color::WHITE, Color::WHITE, Color::WHITE}
        });

        BufferedPpu::on();
        if !consteval { Ppu::wait(); }

        asm volatile(".Lbrk: BRK\n"
                     ".byte 0\n"
                     "JMP .Lbrk");
    }


}