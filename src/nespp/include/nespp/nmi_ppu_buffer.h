/**
 * @author Steven Goldade
 * @date 10/26/2023
 */
#pragma once
#include "low_level.h"
#include "types.h"

static constexpr u8 VRAM_BUFFER_SIZE = 128;

extern "C" u8 __vram_buffer_length; // NOLINT(*-reserved-identifier)
extern "C" u8 __vram_buffer[VRAM_BUFFER_SIZE]; // NOLINT(*-reserved-identifier)
extern "C" LEAF void __nmi_ppu_buffer_copy(); // NOLINT(*-reserved-identifier)

namespace nespp::NMI_PPU_Buffer {
    auto write_buffer(u16 address, const u8* data, u8 length) -> void;
}