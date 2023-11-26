/**
 * @author Steven Goldade
 * @date 11/10/2023
 */
#pragma once
#include <nespp/palette.h>
#include <nespp/ppu.h>

class ScreenFader {
public:
    constexpr ScreenFader(const u8 frame_delay, const nespp::Palette& _palette0, const nespp::Palette& _palette1, const nespp::Palette& _palette2, const nespp::Palette& _palette3) : frame_delay(frame_delay), palette_select(0), last_frame_update(0), palette_0(_palette0), palette_1(_palette1), palette_2(_palette2), palette_3(_palette3) {}
    
    auto constexpr fade_out(const u8 frame_count) noexcept -> bool {
        return internal_fade(frame_count, false);
    }
    auto constexpr fade_in(const u8 frame_count) noexcept -> bool {
        return internal_fade(frame_count, true);
    }
    auto constexpr reset_frame(const u8 frame_count) noexcept -> void {
        last_frame_update = frame_count;
    }
private:
    u8 frame_delay;
    u8 palette_select;
    u8 last_frame_update;
    const nespp::Palette& palette_0;
    const nespp::Palette& palette_1;
    const nespp::Palette& palette_2;
    const nespp::Palette& palette_3;
    
    auto constexpr internal_fade(const u8 current_frame, const bool direction) noexcept -> bool {
        if(frame_delay < (s8)(current_frame - last_frame_update)) {
            last_frame_update = current_frame;
            direction ? palette_select++ : palette_select--;
            
            switch(palette_select) {
                case 0:
                    nespp::BufferedPpu::background_palette.write(palette_0);
                    return !direction;
                case 1:
                    nespp::BufferedPpu::background_palette.write(palette_1);
                    return false;
                case 2:
                    nespp::BufferedPpu::background_palette.write(palette_2);
                    return false;
                case 3:
                    nespp::BufferedPpu::background_palette.write(palette_3);
                    return direction;
            }
        }
        return false;
    }
};