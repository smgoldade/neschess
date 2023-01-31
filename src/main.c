/**
 * Author: Steven Goldade
 */
#include "nes/nes.h"

nes_palette bg_palette[] = {
    {BLACK, WHITE, MEDIUM_GRAY, DARK_GRAY},
    {BLACK, LIGHT_RED, MEDIUM_RED, DARK_RED},
    {BLACK, LIGHT_BLUE, MEDIUM_BLUE, DARK_BLUE},
    {BLACK, LIGHT_GREEN, MEDIUM_GREEN, DARK_GREEN}
};
nes_palette sprite_palette[] = {
    {BLACK, BLACK, PALE_RED, LIGHT_AZURE},
    {BLACK, LIGHT_RED, MEDIUM_RED, DARK_RED},
    {BLACK, LIGHT_BLUE, MEDIUM_BLUE, DARK_BLUE},
    {BLACK, LIGHT_GREEN, MEDIUM_GREEN, DARK_GREEN}
};
attribute_cell attribute_table[] = {
    {0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},
    {0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},
    {0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},
    {0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},
    {0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},
    {0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},
    {0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},
    {0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},
};
const u8 message[] = "Hello World!";
const u8 clear[] = "\0\0\0\0\0\0\0\0\0\0\0\0";

static u8 temp;
static u8 last_upd;
static u8 x;


int main(void) {
    ppu_on();
    ppu_show_left(1,1);
    ppu_nmi_bg_pal_update(bg_palette);
    ppu_nmi_spr_pal_update(sprite_palette);
    ppu_nmi_nt_update(message, sizeof(message)-1, 0, 10, 14);
    ppu_nmi_at_update((const u8*)attribute_table, sizeof(attribute_table),0,0,0);
    // this is legitimately two bytes over the most I can copy in one NMI, but the attribute table will fix itself
    while(1) {
        ppu_wait_nmi();
        temp = ZP_PPU_FRAME_CNT - last_upd;

        if(temp > 4) {
            last_upd = ZP_PPU_FRAME_CNT;
            for(x = 0; x < 64; x++) {
                ++attribute_table[x].bottom_left;
                ++attribute_table[x].bottom_right;
                ++attribute_table[x].top_left;
                ++attribute_table[x].top_right;
            }
            ppu_nmi_at_update((const u8*)attribute_table, sizeof(attribute_table),0,0,0);
        }
    }
    return 0;
}