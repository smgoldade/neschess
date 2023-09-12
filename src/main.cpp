/**
 * Author: Steven Goldade
 */
#include "nes++/nespp.h"

static nes_full_palette bg_palette = {
    MEDIUM_GRAY,
    {WHITE, MEDIUM_GRAY, DARK_GRAY},
    {LIGHT_RED, MEDIUM_RED, DARK_RED},
    {LIGHT_BLUE, MEDIUM_BLUE, DARK_BLUE},
    {LIGHT_GREEN, MEDIUM_GREEN, DARK_GREEN}
};
static nes_full_palette sprite_palette = {
    MEDIUM_GRAY,
    {BLACK, PALE_RED, LIGHT_AZURE},
    {LIGHT_RED, MEDIUM_RED, DARK_RED},
    {LIGHT_BLUE, MEDIUM_BLUE, DARK_BLUE},
    {LIGHT_GREEN, MEDIUM_GREEN, DARK_GREEN}
};
static u8 attribute_table[] = {
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

u8 last_upd;
void attribute_table_cycle() {
    u8 temp = nespp::ppu->get_frame_counter() - last_upd;

    if(temp < 5) {
        return;
    }
    last_upd = nespp::ppu->get_frame_counter();
    for(unsigned char & temp2 : attribute_table) {
        temp2 += 0x55;
    }
    nespp::ppu->attribute_table_update((const u8*)attribute_table, sizeof(attribute_table),nespp::Nametable::ZERO,0,0);
}

int main() {
    nespp::ppu->set_rendering_state(true, true);
    nespp::ppu->set_left_mask(true, true);
    nespp::ppu->set_pattern_tables(false, true);
    nespp::ppu->background_palette_update(&bg_palette);
    nespp::ppu->sprite_palette_update(&bg_palette);
    // sizeof(message)-1 so we don't copy the null terminator from the string
    nespp::ppu->nametable_update(message, sizeof(message)-1, nespp::Nametable::ZERO, 10, 14);
    nespp::ppu->attribute_table_update((const u8*)attribute_table, sizeof(attribute_table),nespp::Nametable::ZERO,0,0);

    while(1) {
        nespp::ppu->wait();
        attribute_table_cycle();
    }
    return 0;
}
