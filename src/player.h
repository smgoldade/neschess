// Author: Steven Goldade
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "physics.h"
#include "types.h"

typedef struct {
    position pos;
    velocity vel;

    u8 sprite_id;
    u8 animation_timer;
    u8 direction : 2;
    u8 animation_state : 2;

} player_t;

extern player_t player;

extern void player_init();
extern void player_update();

#endif