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

int main(void) {
    u8 fc = 0;
    u8 last_upd = 0;
    u8 level = 4;
    u8 dir = 0;
    u8 i = 0;

    ppu_off();
    ppu_bg_palette(bg_palette);

    ppu_set_addr(NT0_ADDR(10, 14));
    ppu_write(message, sizeof(message));
    ppu_on();

    while (1) {
        ppu_wait_nmi();

        fc = ppu_frame_count();
        if((fc-last_upd) > 5) {
            last_upd = fc;
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
            } else if (level == 8) {
                dir = 0;
            }
            ppu_bg_palette(bg_palette);
        }
    }
    return 0;
}