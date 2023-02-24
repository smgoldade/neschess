// Author: Steven Goldade
#ifndef _NES_SPRITE_H_
#define _NES_SPRITE_H_
#include "../core.h"

typedef struct {
    u8 y;
    u8 tile_index;
    u8 attributes;
    u8 x;
} sprite;
extern sprite sprites[64];
#define SPRITE_PALETTE_WRITE(x,y) BIT_WRITE_0_2(x->attributes,y)
#define SPRITE_PRIORITY_WRITE(x,y) BIT_WRITE_5(x->attributes,y)
#define SPRITE_HORIZONTAL_FLIP_WRITE(x,y) BIT_WRITE_6(x->attributes,y)
#define SPRITE_VERTICAL_FLIP_WRITE(x,y) BIT_WRITE_7(x->attributes,y)

#endif //_NES_SPRITE_H_
