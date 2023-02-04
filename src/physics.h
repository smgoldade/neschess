// Author: Steven Goldade
#ifndef _PHYSICS_H_
#define _PHYSICS_H_
#include "types.h"

#define DIRECTION_NORTH 0
#define DIRECTION_EAST 1
#define DIRECTION_SOUTH 2
#define DIRECTION_WEST 3

// Sub-pixel accuracy is used for smoother controller
typedef struct {
    u16 x;
    u16 y;
} position;

typedef struct {
    s16 x;
    s16 y;
} velocity;

extern void physics_update(position* _position, velocity* _velocity);
extern s16 abs16(s16 input);

#endif