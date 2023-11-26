/**
* @author Steven Goldade
* @date 9/11/2023
*/
#include "nespp/ppu.h"

/*
 * Parameters used for buffering. These are declared in the global namespace to prevent name mangling so they can
 * be used by the C function that calls them
 */
nespp::PpuControlRegister buffered_control;
nespp::PpuMaskRegister buffered_mask;
u8 buffered_scroll_x;
u8 buffered_scroll_y;

namespace nespp {
    volatile u8 Ppu::frame_count = 0;
    PpuControlRegister& BufferedPpu::control = buffered_control;
    PpuMaskRegister& BufferedPpu::mask = buffered_mask;
    u8& BufferedPpu::scroll_x = buffered_scroll_x;
    u8& BufferedPpu::scroll_y = buffered_scroll_y;

    Ppu::UnbufferedVramAccessor<PpuNametable, 0x2000, 32> Ppu::nametable_0;
    Ppu::UnbufferedVramAccessor<PpuAttributeTable, 0x23C0, 8> Ppu::attribute_table_0;
    Ppu::UnbufferedVramAccessor<PpuNametable, 0x2400, 32> Ppu::nametable_1;
    Ppu::UnbufferedVramAccessor<PpuAttributeTable, 0x27C0, 8> Ppu::attribute_table_1;
    Ppu::UnbufferedVramAccessor<PpuNametable, 0x2800, 32> Ppu::nametable_2;
    Ppu::UnbufferedVramAccessor<PpuAttributeTable, 0x2BC0, 8> Ppu::attribute_table_2;
    Ppu::UnbufferedVramAccessor<PpuNametable, 0x2C00, 32> Ppu::nametable_3;
    Ppu::UnbufferedVramAccessor<PpuAttributeTable, 0x2FC0, 8> Ppu::attribute_table_3;
    Ppu::UnbufferedVramAccessor<Palette, 0x3F00> Ppu::background_palette;
    Ppu::UnbufferedVramAccessor<Palette, 0x3F10> Ppu::sprite_palette;
    __attribute__((aligned(256))) PpuSprite Ppu::sprites[64]; // alignment necessary to allow OAM DMA to work properly

    BufferedPpu::BufferedVramAccessor<PpuNametable, 0x2000, 32> BufferedPpu::nametable_0;
    BufferedPpu::BufferedVramAccessor<PpuAttributeTable, 0x23C0, 8> BufferedPpu::attribute_table_0;
    BufferedPpu::BufferedVramAccessor<PpuNametable, 0x2400, 32> BufferedPpu::nametable_1;
    BufferedPpu::BufferedVramAccessor<PpuAttributeTable, 0x27C0, 8> BufferedPpu::attribute_table_1;
    BufferedPpu::BufferedVramAccessor<PpuNametable, 0x2800, 32> BufferedPpu::nametable_2;
    BufferedPpu::BufferedVramAccessor<PpuAttributeTable, 0x2BC0, 8> BufferedPpu::attribute_table_2;
    BufferedPpu::BufferedVramAccessor<PpuNametable, 0x2C00, 32> BufferedPpu::nametable_3;
    BufferedPpu::BufferedVramAccessor<PpuAttributeTable, 0x2FC0, 8> BufferedPpu::attribute_table_3;
    BufferedPpu::BufferedVramAccessor<Palette, 0x3F00> BufferedPpu::background_palette;
    BufferedPpu::BufferedVramAccessor<Palette, 0x3F10> BufferedPpu::sprite_palette;

    auto Ppu::is_rendering() -> bool {
        return BufferedPpu::mask.value & 0x18;
    }

    auto Ppu::get_frame_count() -> u8 {
        return frame_count;
    }

    auto Ppu::wait() -> void {
        u8 old_count = frame_count;
        while(frame_count == old_count);
    }

    auto Ppu::background_update() -> void {
        __asm("bit $2002");
        Ppu::scroll() = BufferedPpu::scroll_x;
        Ppu::scroll() = BufferedPpu::scroll_y;
        Ppu::control() = BufferedPpu::control;
    }

    Ppu::Initializer Ppu::init;
    Ppu::Initializer::Initializer() {
        // init control blank
        BufferedPpu::control.value = 0x00;
        Ppu::control() = BufferedPpu::control;

        // clear VRAM on initialization
        Ppu::vram().address = 0x20;
        Ppu::vram().address = 0x00;

        for(u8 i=0; i<0x11; i++)
            for(u8 j=0; j<0xFF; j++)
                Ppu::vram().data = 0x00;

        BufferedPpu::control.vblank_nmi = true;
        Ppu::control() = BufferedPpu::control;

        BufferedPpu::mask.value = 0;
        Ppu::mask() = BufferedPpu::mask;
    }
}

