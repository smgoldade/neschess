// Author: Steven Goldade
#include "nes/nes.h"
#include "player.h"
#include "tileset.h"

player_t player;

void player_init() {
    player.pos.x = 0;
    player.pos.y = 0;
    player.vel.x = 0;
    player.vel.y = 0;

    player.sprite_1 = &sprites[1];
    player.sprite_2 = &sprites[2];
    player.sprite_3 = &sprites[3];
    player.sprite_4 = &sprites[4];
    player.sprite_1->x = 0;
    player.sprite_1->y = 0;
    player.sprite_1->attributes = 0;
    player.sprite_2->x = 0;
    player.sprite_2->y = 0;
    player.sprite_2->attributes = 0;
    player.sprite_3->x = 0;
    player.sprite_3->y = 0;
    player.sprite_3->attributes = 0;
    player.sprite_4->x = 0;
    player.sprite_4->y = 0;
    player.sprite_4->attributes = 0;

    player.animation_state = 0;
    player.animation_timer = 0;
    player.direction = DIRECTION_SOUTH;
}

void player_direction_update() {
    if(player.vel.y < 0) {
        player.direction = DIRECTION_NORTH;
    }
    if(player.vel.y > 0) {
        player.direction = DIRECTION_SOUTH;
    }
    if(abs16(player.vel.x) > abs16(player.vel.y)) {
        if(player.vel.x < 0) {
            player.direction = DIRECTION_WEST;
        } else {
            player.direction = DIRECTION_EAST;
        }
    }
}

void player_metatile_update(u8 top_left, u8 top_right, u8 stand_left, u8 stand_right, u8 walk_left, u8 walk_right) {
    player.sprite_1->x = (player.pos.x >> 8);
    player.sprite_1->y = (player.pos.y >> 8);
    SPRITE_HORIZONTAL_FLIP_WRITE(player.sprite_1, 0);

    player.sprite_2->x = (player.pos.x >> 8) + 8;
    player.sprite_2->y = (player.pos.y >> 8);
    SPRITE_HORIZONTAL_FLIP_WRITE(player.sprite_2, 0);

    player.sprite_3->x = (player.pos.x >> 8);
    player.sprite_3->y = (player.pos.y >> 8) + 8;
    SPRITE_HORIZONTAL_FLIP_WRITE(player.sprite_3, 0);

    player.sprite_4->x = (player.pos.x >> 8) + 8;
    player.sprite_4->y = (player.pos.y >> 8) + 8;
    SPRITE_HORIZONTAL_FLIP_WRITE(player.sprite_4, 0);

    switch(player.animation_state) {
        default:
        case 0:
            player.sprite_1->tile_index = top_left;
            player.sprite_2->tile_index = top_right;
            player.sprite_3->tile_index = stand_left;
            player.sprite_4->tile_index = stand_right;
            break;
        case 1:
            player.sprite_1->tile_index = top_left;
            player.sprite_2->tile_index = top_right;
            player.sprite_3->tile_index = walk_left;
            player.sprite_4->tile_index = walk_right;
            break;
        case 2:
            player.sprite_1->tile_index = top_left;
            player.sprite_2->tile_index = top_right;
            player.sprite_3->tile_index = walk_right;
            SPRITE_HORIZONTAL_FLIP_WRITE(player.sprite_3, 1);
            player.sprite_4->tile_index = walk_left;
            SPRITE_HORIZONTAL_FLIP_WRITE(player.sprite_4, 1);
            break;
    }
}

void player_sprite_update() {
    switch(player.direction) {
        case DIRECTION_NORTH:
            player_metatile_update(
                SPRITE_CHARACTER_NORTH_LEFT,
                SPRITE_CHARACTER_NORTH_RIGHT,
                SPRITE_CHARACTER_NORTH_STAND_LEFT,
                SPRITE_CHARACTER_NORTH_STAND_RIGHT,
                SPRITE_CHARACTER_NORTH_WALK_LEFT,
                SPRITE_CHARACTER_NORTH_WALK_RIGHT
            );
            break;
        case DIRECTION_SOUTH:
            player_metatile_update(
                SPRITE_CHARACTER_SOUTH_LEFT,
                SPRITE_CHARACTER_SOUTH_RIGHT,
                SPRITE_CHARACTER_SOUTH_STAND_LEFT,
                SPRITE_CHARACTER_SOUTH_STAND_RIGHT,
                SPRITE_CHARACTER_SOUTH_WALK_LEFT,
                SPRITE_CHARACTER_SOUTH_WALK_RIGHT
            );
            break;
        case DIRECTION_EAST:
        case DIRECTION_WEST:
            if(player.direction == DIRECTION_WEST) {
                SPRITE_HORIZONTAL_FLIP_WRITE(player.sprite_1, 1);
                SPRITE_HORIZONTAL_FLIP_WRITE(player.sprite_2, 1);
            } else {
                SPRITE_HORIZONTAL_FLIP_WRITE(player.sprite_1, 0);
                SPRITE_HORIZONTAL_FLIP_WRITE(player.sprite_2, 0);
            }
            player.sprite_1->x = (player.pos.x >> 8);
            player.sprite_1->y = (player.pos.y >> 8);
            player.sprite_2->x = (player.pos.x >> 8);
            player.sprite_2->y = (player.pos.y >> 8) + 8;
            player.sprite_3->y = 0xFF;
            player.sprite_4->y = 0xFF;

            switch(player.animation_state) {
                default:
                case 0:
                    player.sprite_1->tile_index = SPRITE_CHARACTER_EAST_TOP;
                    player.sprite_2->tile_index = SPRITE_CHARACTER_EAST_STAND;
                    break;
                case 1:
                    player.sprite_1->tile_index = SPRITE_CHARACTER_EAST_TOP;
                    player.sprite_2->tile_index = SPRITE_CHARACTER_EAST_WALK_1;
                    break;
                case 2:
                    player.sprite_1->tile_index = SPRITE_CHARACTER_EAST_TOP;
                    player.sprite_2->tile_index = SPRITE_CHARACTER_EAST_WALK_2;
                    break;
            }
            break;
    }
}

void player_animation_update() {
    ++player.animation_timer;
    if(player.animation_timer > 4) {
        ++player.animation_state;
        player.animation_timer = 0;
        if(player.animation_state > 2) {
            player.animation_state = 0;
        }
    }

    if(player.vel.x == 0 && player.vel.y == 0) {
        player.animation_state = 0;
        player.animation_timer = 0;
    }
}

void player_update() {
    physics_update(&player.pos, &player.vel);
    player_direction_update();
    player_sprite_update();
    player_animation_update();
}
