/**
 * Author: Steven Goldade
 */
#include "nes/nes.h"
#include "player.h"

nes_palette bg_palette[] = {
    {MEDIUM_GRAY, WHITE, MEDIUM_GRAY, DARK_GRAY},
    {MEDIUM_GRAY, LIGHT_RED, MEDIUM_RED, DARK_RED},
    {MEDIUM_GRAY, LIGHT_BLUE, MEDIUM_BLUE, DARK_BLUE},
    {MEDIUM_GRAY, LIGHT_GREEN, MEDIUM_GREEN, DARK_GREEN}
};
nes_palette sprite_palette[] = {
    {MEDIUM_GRAY, BLACK, PALE_RED, LIGHT_AZURE},
    {MEDIUM_GRAY, LIGHT_RED, MEDIUM_RED, DARK_RED},
    {MEDIUM_GRAY, LIGHT_BLUE, MEDIUM_BLUE, DARK_BLUE},
    {MEDIUM_GRAY, LIGHT_GREEN, MEDIUM_GREEN, DARK_GREEN}
};
u8 attribute_table[] = {
    0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,
    0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,
    0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,
    0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,
    0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,
    0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,
    0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,
    0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,
};
const u8 message[] = "Hello World!";

static u8 temp;
static u8 temp2;
static u8 last_upd;

static u8 controller_1;

void controller_update(void);
void attribute_table_cycle(void);

int main(void) {
    ppu_on();
    ppu_show_left(1,1);
    ppu_pattern_table(0,1);
    ppu_nmi_bg_pal_update(bg_palette);
    ppu_nmi_spr_pal_update(sprite_palette);
    ppu_nmi_nt_update(message, sizeof(message)-1, 0, 10, 14);
    ppu_nmi_at_update((const u8*)attribute_table, sizeof(attribute_table),0,0,0);
    // this is legitimately two bytes over the most I can copy in one NMI, but the attribute table will fix itself

    player_init();

    while(1) {
        ppu_wait_nmi();
        controller_update();
        attribute_table_cycle();
        player_update();
    }
    return 0;
}

void controller_update(void) {
    controller_1 = input_c1_held();
    if(BUTTON_UP(controller_1)) {
        player.vel.y -= 0x20;
    }
    if(BUTTON_DOWN(controller_1)) {
        player.vel.y += 0x20;
    }
    if(BUTTON_LEFT(controller_1)) {
        player.vel.x -= 0x20;
    }
    if(BUTTON_RIGHT(controller_1)) {
        player.vel.x += 0x20;
    }

    controller_1 = input_c1_released();
    if(BUTTON_UP(controller_1) || BUTTON_DOWN(controller_1)) {
        player.vel.y = 0;
    }
    if(BUTTON_LEFT(controller_1) || BUTTON_RIGHT(controller_1)) {
        player.vel.x = 0;
    }

    if(player.vel.x < -0x200) {
        player.vel.x = -0x200;
    }
    if(player.vel.x > 0x200) {
        player.vel.x = 0x200;
    }
    if(player.vel.y < -0x200) {
        player.vel.y = -0x200;
    }
    if(player.vel.y > 0x200) {
        player.vel.y = 0x200;
    }
}

void attribute_table_cycle(void) {
    temp = ZP_PPU_FRAME_CNT - last_upd;

    if(temp < 5) {
        return;
    }
    last_upd = ZP_PPU_FRAME_CNT;
    for(temp2 = 0; temp2 < 64; ++temp2) {
        attribute_table[temp2] += 0x55;
    }
    ppu_nmi_at_update((const u8*)attribute_table, sizeof(attribute_table),0,0,0);
}