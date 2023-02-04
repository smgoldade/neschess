// Author: Steven Goldade
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "physics.h"
#include "types.h"

typedef struct {
    position pos;
    velocity vel;

    sprite* sprite_1;
    sprite* sprite_2;
    sprite* sprite_3;
    sprite* sprite_4;

    u8 animation_timer;
    u8 direction;
    u8 animation_state;

} player_t;

extern player_t player;

extern void player_init();
extern void player_update();

#endif