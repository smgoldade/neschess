#ifndef _NES_H_
#define _NES_H_

typedef unsigned char u8;
typedef char s8;
typedef unsigned int u16;
typedef signed int s16;
typedef unsigned long u32;
typedef signed long s32;

void __fastcall__ ppu_set_addr(u16 addr);
void __fastcall__ ppu_write(u8* data, u16 size);
void __fastcall__ ppu_off(void);
void __fastcall__ ppu_on(void);

/**
 * Nametable
 */
#define NAMETABLE_0 0x2000
#define ATTRIBUTE_TABLE_0 0x23C0
#define NAMETABLE_1 0x2400
#define ATTRIBUTE_TABLE_1 0x27C0
#define NAMETABLE_2 0x2800
#define ATTRIBUTE_TABLE_2 0x2BC0
#define NAMETABLE_3 0x2C00
#define ATTRIBUTE_TABLE_3 0x2FC0

#define NT_WIDTH 32
#define NT_HEIGHT 30
#define NT0_ADDR(x,y) (NAMETABLE_0 | (y << 5) | x)
#define NT1_ADDR(x,y) (NAMETABLE_1 | (y << 5) | x)
#define NT2_ADDR(x,y) (NAMETABLE_2 | (y << 5) | x)
#define NT3_ADDR(x,y) (NAMETABLE_3 | (y << 5) | x)

/**
 * Palette
 */
#define BACKGROUND_COLOR 0x3F00
#define BACKGROUND_PALETTE_0 0x3F01
#define BACKGROUND_PALETTE_1 0x3F05
#define BACKGROUND_PALETTE_2 0x3F09
#define BACKGROUND_PALETTE_3 0x3F0D

#define DARK_GRAY 0x00
#define DARK_AZURE 0x01
#define DARK_BLUE 0x02
#define DARK_VIOLET 0x03
#define DARK_MAGENTA 0x04
#define DARK_ROSE 0x05
#define DARK_RED 0x06
#define DARK_ORANGE 0x07
#define DARK_OLIVE 0x08
#define DARK_CHARTREUSE 0x09
#define DARK_GREEN 0x0A
#define DARK_SPRING 0x0B
#define DARK_CYAN 0x0C
#define ULTRA_BLACK 0x0D // should be avoided, causes "blacker than black"
#define MIRROR_BLACK 0x0E
#define BLACK 0x0F
#define MEDIUM_GRAY 0x10
#define MEDIUM_AZURE 0x11
#define MEDIUM_BLUE 0x12
#define MEDIUM_VIOLET 0x13
#define MEDIUM_MAGENTA 0x14
#define MEDIUM_ROSE 0x15
#define MEDIUM_RED 0x16
#define MEDIUM_ORANGE 0x17
#define MEDIUM_OLIVE 0x18
#define MEDIUM_CHARTREUSE 0x19
#define MEDIUM_GREEN 0x1A
#define MEDIUM_SPRING 0x1B
#define MEDIUM_CYAN 0x1C
#define WHITE 0x20
#define LIGHT_AZURE 0x21
#define LIGHT_BLUE 0x22
#define LIGHT_VIOLET 0x23
#define LIGHT_MAGENTA 0x24
#define LIGHT_ROSE 0x25
#define LIGHT_RED 0x26
#define LIGHT_ORANGE 0x27
#define LIGHT_OLIVE 0x28
#define LIGHT_CHARTREUSE 0x29
#define LIGHT_GREEN 0x2A
#define LIGHT_SPRING 0x2B
#define LIGHT_CYAN 0x2C
#define MIRROR_DARK_GRAY 0x2D
#define MIRROR_BLACK_2 0x2E
#define MIRROR_BLACK_3 0x2F
#define ULTRA_WHITE 0x30 // fades to black slower than standard white
#define PALE_AZURE 0x31
#define PALE_BLUE 0x32
#define PALE_VIOLET 0x33
#define PALE_MAGENTA 0x34
#define PALE_ROSE 0x35
#define PALE_RED 0x36
#define PALE_ORANGE 0x37
#define PALE_OLIVE 0x38
#define PALE_CHARTREUSE 0x39
#define PALE_GREEN 0x3A
#define PALE_SPRING 0x3B
#define PALE_CYAN 0x3C
#define MIRROR_MEDIUM_GRAY 0x3D
#define MIRROR_BLACK_4 0x3E
#define MIRROR_BLACK_5 0x3F
#endif