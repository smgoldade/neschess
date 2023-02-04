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

    player.sprite_id = 1;
    sprites[player.sprite_id].x = 0;
    sprites[player.sprite_id].y = 0;
    sprites[player.sprite_id].attributes.palette = 0;
    sprites[player.sprite_id].attributes.unused = 0;
    sprites[player.sprite_id].attributes.priority = 0;
    sprites[player.sprite_id].attributes.horizontal_flip = 0;
    sprites[player.sprite_id].attributes.vertical_flip = 0;
    sprites[player.sprite_id+1].x = 0;
    sprites[player.sprite_id+1].y = 0;
    sprites[player.sprite_id+1].attributes.palette = 0;
    sprites[player.sprite_id+1].attributes.unused = 0;
    sprites[player.sprite_id+1].attributes.priority = 0;
    sprites[player.sprite_id+1].attributes.horizontal_flip = 0;
    sprites[player.sprite_id+1].attributes.vertical_flip = 0;
    sprites[player.sprite_id+2].x = 0;
    sprites[player.sprite_id+2].y = 0;
    sprites[player.sprite_id+2].attributes.palette = 0;
    sprites[player.sprite_id+2].attributes.unused = 0;
    sprites[player.sprite_id+2].attributes.priority = 0;
    sprites[player.sprite_id+2].attributes.horizontal_flip = 0;
    sprites[player.sprite_id+2].attributes.vertical_flip = 0;
    sprites[player.sprite_id+3].x = 0;
    sprites[player.sprite_id+3].y = 0;
    sprites[player.sprite_id+3].attributes.palette = 0;
    sprites[player.sprite_id+3].attributes.unused = 0;
    sprites[player.sprite_id+3].attributes.priority = 0;
    sprites[player.sprite_id+3].attributes.horizontal_flip = 0;
    sprites[player.sprite_id+3].attributes.vertical_flip = 0;

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
    sprites[player.sprite_id].x = (player.pos.x >> 8);
    sprites[player.sprite_id].y = (player.pos.y >> 8);
    sprites[player.sprite_id].attributes.horizontal_flip = 0;

    sprites[player.sprite_id+1].x = (player.pos.x >> 8) + 8;
    sprites[player.sprite_id+1].y = (player.pos.y >> 8);
    sprites[player.sprite_id+1].attributes.horizontal_flip = 0;

    sprites[player.sprite_id+2].x = (player.pos.x >> 8);
    sprites[player.sprite_id+2].y = (player.pos.y >> 8) + 8;
    sprites[player.sprite_id+2].attributes.horizontal_flip = 0;

    sprites[player.sprite_id+3].x = (player.pos.x >> 8) + 8;
    sprites[player.sprite_id+3].y = (player.pos.y >> 8) + 8;
    sprites[player.sprite_id+3].attributes.horizontal_flip = 0;

    switch(player.animation_state) {
        default:
        case 0:
            sprites[player.sprite_id].tile_index = top_left;
            sprites[player.sprite_id+1].tile_index = top_right;
            sprites[player.sprite_id+2].tile_index = stand_left;
            sprites[player.sprite_id+3].tile_index = stand_right;
            break;
        case 1:
            sprites[player.sprite_id].tile_index = top_left;
            sprites[player.sprite_id+1].tile_index = top_right;
            sprites[player.sprite_id+2].tile_index = walk_left;
            sprites[player.sprite_id+3].tile_index = walk_right;
            break;
        case 2:
            sprites[player.sprite_id].tile_index = top_left;
            sprites[player.sprite_id+1].tile_index = top_right;
            sprites[player.sprite_id+2].tile_index = walk_right;
            sprites[player.sprite_id+2].attributes.horizontal_flip = 1;
            sprites[player.sprite_id+3].tile_index = walk_left;
            sprites[player.sprite_id+3].attributes.horizontal_flip = 1;
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
                sprites[player.sprite_id].attributes.horizontal_flip = 1;
                sprites[player.sprite_id+1].attributes.horizontal_flip = 1;
            } else {
                sprites[player.sprite_id].attributes.horizontal_flip = 0;
                sprites[player.sprite_id+1].attributes.horizontal_flip = 0;
            }
            sprites[player.sprite_id].x = (player.pos.x >> 8);
            sprites[player.sprite_id].y = (player.pos.y >> 8);
            sprites[player.sprite_id+1].x = (player.pos.x >> 8);
            sprites[player.sprite_id+1].y = (player.pos.y >> 8) + 8;
            sprites[player.sprite_id+2].y = 0xFF;
            sprites[player.sprite_id+3].y = 0xFF;

            switch(player.animation_state) {
                default:
                case 0:
                    sprites[player.sprite_id].tile_index = SPRITE_CHARACTER_EAST_TOP;
                    sprites[player.sprite_id+1].tile_index = SPRITE_CHARACTER_EAST_STAND;
                    break;
                case 1:
                    sprites[player.sprite_id].tile_index = SPRITE_CHARACTER_EAST_TOP;
                    sprites[player.sprite_id+1].tile_index = SPRITE_CHARACTER_EAST_WALK_1;
                    break;
                case 2:
                    sprites[player.sprite_id].tile_index = SPRITE_CHARACTER_EAST_TOP;
                    sprites[player.sprite_id+1].tile_index = SPRITE_CHARACTER_EAST_WALK_2;
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
