// Author: Steven Goldade
#include "nes_ppu.h"

/*
 * Parameters used for buffering. This class does not perform any actual changes on VRAM or PPU state
 * until background_update() is called. These values are also declared globally as they are used by the global
 * assembly function that was written to do the background update.
 */
u8 buffered_control;
u8 buffered_mask;
u8 buffered_scroll_x;
u8 buffered_scroll_y;

/**
 * The length of bytes currently valid in the VRAM transfer vram_buffer
 */
u8 vram_buffer_length;
/**
 * The buffered data to transfer to VRAM. They are stored in the format of ADDR_HI ADDR_LO LEN D[0] ... D[LEN] and repeated
 */
u8 vram_buffer[256];

namespace nespp {
    auto PPU::set_rendering_state(const bool background, const bool sprite) -> void {
        background ? buffered_mask |= 0x08 : buffered_mask &= 0xF7;
        sprite ? buffered_mask |= 0x10 : buffered_mask &= 0xEF;
    }

    auto PPU::set_left_mask(const bool background, const bool sprite) -> void {
        background ? buffered_mask |= 0x02 : buffered_mask &= 0xFD;
        sprite ? buffered_mask |= 0x04 : buffered_mask &= 0xFB;
    }

    auto PPU::set_emphasis(const bool red, const bool green, const bool blue) -> void {
        red ? buffered_mask |= 0x20 : buffered_mask &= 0xDF;
        green ? buffered_mask |= 0x40 : buffered_mask &= 0xBF;
        blue ? buffered_mask |= 0x80 : buffered_mask &= 0x7F;
    }

    auto PPU::set_grayscale(const bool enable) -> void {
        enable ? buffered_mask |= 0x01 : buffered_mask &= 0xFE;
    }

    auto PPU::set_scroll(const u8 x, const u8 y) -> void {
        buffered_scroll_x = x;
        buffered_scroll_y = y;
    }

    auto PPU::set_nametable(const Nametable nametable) -> void {
        buffered_control &= 0xFC;
        buffered_control |= (u8)nametable;
    }

    auto PPU::set_pattern_tables(const bool background, const bool sprite) -> void {
        background ? buffered_control |= 0x10 : buffered_control &= 0xEF;
        sprite ? buffered_control |= 0x08 : buffered_control &= 0xF7;
    }

    auto PPU::set_sprite_size(const bool large) -> void {
        large ? buffered_control |= 0x20 : buffered_control &= 0xDF;
    }

    auto PPU::set_master_mode(const bool master) -> void {
        master ? buffered_control |= 0x40 : buffered_control &= 0xBF;
    }

    auto PPU::set_nmi_enable(const bool enable) -> void {
        enable ? PPUREG.control |= 0x80 : PPUREG.control &= 0x7F;
    }

    auto PPU::is_rendering() const -> bool {
        return buffered_mask & 0x18;
    }

    auto PPU::get_frame_counter() const -> u8 {
        return frame_count;
    }

    auto PPU::wait() const -> void {
        u8 old_count = frame_count;
        while(frame_count == old_count);
    }

    auto PPU::background_update() -> void {
        // call the external background update function, which is written in pure assembly for maximum
        // speed. Even with LLVM-MOS compiling efficiency, it could not beat the handcoded assembly speed.
        ppu_background_update();
    }

    auto PPU::nametable_update(const u8* const data, const u8 size, const Nametable nametable, const u8 x, const u8 y) -> void {
        vram_buffer_insert(0x2000 + 0x400 * (u8)nametable + 0x20 * y + x, data, size);
    }

    auto PPU::attribute_table_update(const u8* const data, const u8 size, const nespp::Nametable nametable, const u8 x, const u8 y) -> void {
        vram_buffer_insert(0x23C0 + 0x400 * (u8)nametable + 0x8 * y + x, data, size);
    }

    auto PPU::background_palette_update(const nes_full_palette* const palette) -> void {
        vram_palette_insert(0x3F00, palette);
    }

    auto PPU::sprite_palette_update(const nes_full_palette* const palette) -> void {
        vram_palette_insert(0x3F10, palette);
    }

    auto PPU::get_instance() -> PPU& {
        static PPU instance;
        return instance;
    }

    auto PPU::nmi_update() -> void {
        background_update();
        frame_count++;
    }

    PPU::PPU() {
        // clear the nametables on initialization so there is a known clean state
        PPUREG.vram.address = 0x20;
        PPUREG.vram.address = 0x00;

        for(u16 i=0; i<0x1000; ++i)
            PPUREG.vram.data = 0x00;

        vram_buffer_length = 0;
        PPUREG.control = 0x80;
        buffered_control = 0x80;
        buffered_mask = 0x00;
        buffered_scroll_x = 0;
        buffered_scroll_y = 0;
    }

    auto PPU::vram_buffer_insert(const u16 address, const u8* const data, const u8 size) -> void {
        vram_buffer[vram_buffer_length++] = address >> 0x8;
        vram_buffer[vram_buffer_length++] = address & 0xFF;
        vram_buffer[vram_buffer_length++] = size;

        for(u8 i=0; i<size; i++)
            vram_buffer[vram_buffer_length++] = data[i];
    }

    auto PPU::vram_palette_insert(const u16 address, const nes_full_palette* const palette) -> void {
        vram_buffer[vram_buffer_length++] = address >> 0x8;
        vram_buffer[vram_buffer_length++] = address & 0xFF;
        vram_buffer[vram_buffer_length++] = 16;
        vram_buffer[vram_buffer_length++] = palette->background_color;
        vram_buffer[vram_buffer_length++] = palette->palette_0.color_1;
        vram_buffer[vram_buffer_length++] = palette->palette_0.color_2;
        vram_buffer[vram_buffer_length++] = palette->palette_0.color_3;
        vram_buffer[vram_buffer_length++] = palette->background_color;
        vram_buffer[vram_buffer_length++] = palette->palette_1.color_1;
        vram_buffer[vram_buffer_length++] = palette->palette_1.color_2;
        vram_buffer[vram_buffer_length++] = palette->palette_1.color_3;
        vram_buffer[vram_buffer_length++] = palette->background_color;
        vram_buffer[vram_buffer_length++] = palette->palette_2.color_1;
        vram_buffer[vram_buffer_length++] = palette->palette_2.color_2;
        vram_buffer[vram_buffer_length++] = palette->palette_2.color_3;
        vram_buffer[vram_buffer_length++] = palette->background_color;
        vram_buffer[vram_buffer_length++] = palette->palette_3.color_1;
        vram_buffer[vram_buffer_length++] = palette->palette_3.color_2;
        vram_buffer[vram_buffer_length++] = palette->palette_3.color_3;
    }

    PPU* const ppu = &PPU::get_instance();
}

