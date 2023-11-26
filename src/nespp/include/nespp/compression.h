/**
 * @author Steven Goldade
 * @date 11/7/2023
 */
#pragma once
#include "ppu.h"
#include "types.h"

namespace nespp::RunLengthEncoding {
    template<VramAccessor T>
    auto constexpr decompress_to(const T& vram_accessor, const u8* data) -> void {
        const u8 marker = data[0];
        u8 last_byte = 0;
        u16 bytes_written = 0;
        u16 i = 0;
        while(true) {
            if(data[++i] != marker) {
                last_byte = data[i];
                vram_accessor.write_partial(&last_byte, 1, bytes_written++);
            } else {
                u8 run_length = data[++i];
                if(run_length == 0) return;
                
                while(run_length--) {
                    vram_accessor.write_partial(&last_byte, 1, bytes_written++);
                }
            }
        }
    }
    
}