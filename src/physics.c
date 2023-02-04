// Author: Steven Goldade
#include "physics.h"

void physics_update(position* _position, velocity* _velocity) {
    if(_velocity->x < 0) {
        if(_position->x < abs16(_velocity->x)) {
            _position->x = 0;
            _velocity->x = 0;
        }
    }
    if(_velocity->x > 0) {
        if((0xFFFF - _position->x) < _velocity->x) {
            _position->x = 0xFFFF;
            _velocity->x = 0;
        }
    }
    if(_velocity->y < 0) {
        if(_position->y < abs16(_velocity->y)) {
            _position->y = 0;
            _velocity->y = 0;
        }
    }
    if(_velocity->y > 0) {
        if((0xFFFF - _position->y) < _velocity->y) {
            _position->y = 0xFFFF;
            _velocity->y = 0;
        }
    }
    _position->x += _velocity->x;
    _position->y += _velocity->y;
}

extern s16 abs16(s16 input) {
    if(input < 0) {
        input = -input;
    }
    return input;
}