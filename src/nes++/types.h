// Author: Steven Goldade
#ifndef _TYPES_H_
#define _TYPES_H_
#include <cstdint>

// Oh no, I shortened the stdint definitions and some people hate this. *shocked Pikachu face*
typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;

extern u8 abs8(s8 a);
extern u16 abs16(s16 a);

#endif