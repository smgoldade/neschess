/**
 * @author Steven Goldade
 * @date 10/26/2023
 */
#include "nespp/nmi_ppu_buffer.h"

u8 __vram_buffer_length = 0;
u8 __vram_buffer[VRAM_BUFFER_SIZE];

auto nespp::NMI_PPU_Buffer::write_buffer(const u16 address, const u8* data, const u8 length) -> void {
    __vram_buffer[__vram_buffer_length++] = length;
    __vram_buffer[__vram_buffer_length++] = address >> 8;
    __vram_buffer[__vram_buffer_length++] = address & 0xFF;
    for(auto i=0; i<length; ++i) {
        __vram_buffer[__vram_buffer_length++] = data[i];
    }
}