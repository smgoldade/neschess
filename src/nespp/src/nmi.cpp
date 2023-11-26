/**
 * @author Steven Goldade
 * @date 11/8/2023
 */
#include "nespp/joypad.h"
#include "nespp/ppu.h"

void __nmi_update() {
    if(nespp::Ppu::is_rendering()) {
        nespp::Ppu::oam_dma() = reinterpret_cast<u16>(&nespp::Ppu::sprites) >> 8;
        __nmi_ppu_buffer_copy();
        nespp::Ppu::background_update();
    }
    __poll_joypad();
    nespp::Ppu::frame_count = nespp::Ppu::frame_count + 1;
    nespp::Ppu::mask() = nespp::BufferedPpu::mask;
}