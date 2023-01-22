/**
 * Author: Steven Goldade
 */
#include "nes/nes.h"

nes_palette bg_palette[] = {
    {BLACK, WHITE, MEDIUM_GRAY, DARK_GRAY},
    {BLACK, WHITE, MEDIUM_GRAY, DARK_GRAY},
    {BLACK, WHITE, MEDIUM_GRAY, DARK_GRAY},
    {BLACK, WHITE, MEDIUM_GRAY, DARK_GRAY}
};
const u8 message[] = "Hello World!";
const u8 clear[] = "\0\0\0\0\0\0\0\0\0\0\0\0";

int main(void) {
    u8 fd = 0;
    u8 last_upd = 0;
    u8 last_upd_pal = 0;
    u8 level = 4;
    u8 dir = 0;
    u8 x = 0;
    s8 x_dir = 1;
    u8 y = 0;
    s8 y_dir = -1;

    ppu_off();
    ppu_bg_palette(bg_palette);
    ppu_on();

    while(1) {
        ppu_wait_nmi();

        fd = ZP_PPU_FRAME_CNT - last_upd;
        if(fd > 1) {
            last_upd = ZP_PPU_FRAME_CNT;
            ppu_nmi_nt_update(clear, sizeof(clear), 0, x, y);
            x += x_dir;
            y += y_dir;
            if(x == 0xFF) {
                x = 0;
                x_dir = 1;
            }
            if(x == NT_WIDTH-sizeof(message)+1) {
                x_dir = -1;
            }
            if(y == 0xFF) {
                y = 0;
                y_dir = 1;
            }
            if(y == NT_HEIGHT-1) {
                y_dir = -1;
            }
            ppu_nmi_nt_update(message, sizeof(message), 0, x, y);
        }
        fd = ZP_PPU_FRAME_CNT - last_upd_pal;
        if(fd > 5) {
            last_upd_pal = ZP_PPU_FRAME_CNT;
            if(dir) {
                ++level;
                bg_palette[0].color_1 = ppu_lighten_color(bg_palette[0].color_1);
                bg_palette[0].color_2 = ppu_lighten_color(bg_palette[0].color_2);
                bg_palette[0].color_3 = ppu_lighten_color(bg_palette[0].color_3);
            } else {
                --level;
                bg_palette[0].color_1 = ppu_darken_color(bg_palette[0].color_1);
                bg_palette[0].color_2 = ppu_darken_color(bg_palette[0].color_2);
                bg_palette[0].color_3 = ppu_darken_color(bg_palette[0].color_3);
            }
            if(level == 0) {
                dir = 1;
            } else if (level == 6) {
                dir = 0;
            }
            ppu_bg_palette(bg_palette);
        }
    }
    return 0;
}