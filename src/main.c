/**
 * Author: Steven Goldade
 */
#include "nes/nes.h"

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
static u8 temp2;
static u8 temp3;
static u8 last_upd;

static u8 player_x = 20;
static u8 player_y = 20;
static u8 player_sprite_id = 0;
static u8 player_sprite_palette = 0;
static u8 player_moving = 0;
static u8 player_animation_frame = 0;
static controller controller_1;

void movement(void);
void attribute_table_cycle(void);
void update_player_sprite(void);

int main(void) {
    ppu_on();
    ppu_show_left(1,1);
    ppu_pattern_table(0,1);
    ppu_nmi_bg_pal_update(bg_palette);
    ppu_nmi_spr_pal_update(sprite_palette);
    ppu_nmi_nt_update(message, sizeof(message)-1, 0, 10, 14);
    ppu_nmi_at_update((const u8*)attribute_table, sizeof(attribute_table),0,0,0);
    // this is legitimately two bytes over the most I can copy in one NMI, but the attribute table will fix itself

    sprites[player_sprite_id].tile_index = 0;
    sprites[player_sprite_id].attributes.palette = player_sprite_palette;
    sprites[player_sprite_id+1].tile_index = 1;
    sprites[player_sprite_id+1].attributes.palette = player_sprite_palette;
    sprites[player_sprite_id+2].tile_index = 2;
    sprites[player_sprite_id+2].attributes.palette = player_sprite_palette;
    sprites[player_sprite_id+3].tile_index = 3;
    sprites[player_sprite_id+3].attributes.palette = player_sprite_palette;

    while(1) {
        ppu_wait_nmi();
        movement();
        attribute_table_cycle();
        update_player_sprite();
    }
    return 0;
}

void movement(void) {
    player_moving = 0;
    controller_1 = input_c1_held();
    if(controller_1.UP) {
        --player_y;
        if(player_y == 0xFF) {
            player_y = 0;
        }
        player_moving = 1;
    }
    if(controller_1.DOWN) {
        ++player_y;
        if(player_y == 0xEF) {
            player_y = 0xEE;
        }
        player_moving = 1;
    }
    if(controller_1.LEFT) {
        --player_x;
        if(player_x == 0xFF) {
            player_x = 0;
        }
        player_moving = 1;
    }
    if(controller_1.RIGHT) {
        ++player_x;
        if(player_x == 0) {
            player_x = 0xFF;
        }
        player_moving = 1;
    }
    if(player_moving) {
        ++player_animation_frame;
        if(player_animation_frame > 11) {
            player_animation_frame = 0;
        }
    } else {
        player_animation_frame = 0;
    }
}

void attribute_table_cycle(void) {
    temp = ZP_PPU_FRAME_CNT - last_upd;

    if(temp > 4) {
        last_upd = ZP_PPU_FRAME_CNT;
        for(temp2 = 0; temp2 < 64; ++temp2) {
            ++attribute_table[temp2].bottom_left;
            ++attribute_table[temp2].bottom_right;
            ++attribute_table[temp2].top_left;
            ++attribute_table[temp2].top_right;
        }
        ppu_nmi_at_update((const u8*)attribute_table, sizeof(attribute_table),0,0,0);
    }
}

void update_player_sprite(void) {
    for(temp = 0; temp < 4; ++temp) {
        if(temp & 1){
            temp2 = 8;
        } else {
            temp2 = 0;
        }
        if(temp > 1) {
            temp3 = 8;
        } else {
            temp3 = 0;
        }
        sprites[player_sprite_id+temp].y = player_y + temp3;
        sprites[player_sprite_id+temp].x = player_x + temp2;
    }

    switch(player_animation_frame) {
        default:
        case 0:
            sprites[player_sprite_id+2].tile_index = 2;
            sprites[player_sprite_id+2].attributes.horizontal_flip = 0;
            sprites[player_sprite_id+3].tile_index = 3;
            sprites[player_sprite_id+3].attributes.horizontal_flip = 0;
            break;
        case 4:
            sprites[player_sprite_id+2].tile_index = 4;
            sprites[player_sprite_id+3].tile_index = 5;
            break;
        case 8:
            sprites[player_sprite_id+2].tile_index = 5;
            sprites[player_sprite_id+2].attributes.horizontal_flip = 1;
            sprites[player_sprite_id+3].tile_index = 4;
            sprites[player_sprite_id+3].attributes.horizontal_flip = 1;
    }
}