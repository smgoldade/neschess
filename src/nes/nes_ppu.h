// Author: Steven Goldade
#ifndef _NES_PPU_H_
#define _NES_PPU_H_
#include "../core.h"
/**
 * Turns off the PPU background and sprite rendering. Change takes effect after next NMI interrupt
 */
extern void __fastcall__ ppu_off(void);
/**
 * Turns on the PPU background and sprite rendering. Change takes effect after next NMI interrupt
 */
extern void __fastcall__ ppu_on(void);
/**
 * Adjusts the PPU's rendering settings. Change takes effect after next NMI interrupt
 * @param background 0 to turn off, 1 to turn on
 * @param sprite 0 to turn off, 1 to turn on
 */
extern void __fastcall__ ppu_rendering(u8 background, u8 sprite);
/**
 * Adjusts the PPU's show of the left most 8 pixels.
 * @param background 0 to hide, 1 to show
 * @param sprite 0 to hide, 1 to show
 */
extern void __fastcall__ ppu_show_left(u8 background, u8 sprite);
/**
 * Adjusts the PPU's emphasis settings
 * @param red 0 to turn off, 1 to turn on
 * @param green 0 to turn off, 1 to turn on
 * @param blue 0 to turn off, 1 to turn on
 */
extern void __fastcall__ ppu_emphasis(u8 red, u8 green, u8 blue);
/**
 * Adjusts the PPU's grayscale setting
 * @param enable 0 to turn off, 1 to turn on
 */
extern void __fastcall__ ppu_greyscale(u8 enable);
/**
 * Adjusts the PPU's scroll setting. Set at the next NMI.
 * @param x the x value to scroll to
 * @param y the y value to scroll to
 */
extern void __fastcall__ ppu_scroll(u8 x, u8 y);
/**
  * Adjusts the PPUs current rendered nametable. Set at the next NMI.
  * Also known as a "coarse scroll"
  * @param nametable
  */
extern void __fastcall__ ppu_nametable(u8 nametable);
/**
 * Adjusts the PPUs current pattern table for background and sprites. Set at the next NMI.
 * @param background 0 or 1 for the appropriate pattern table
 * @param sprite 0 or 1 for the appropriate pattern table
 */
extern void __fastcall__ ppu_pattern_table(u8 background, u8 sprite);
/**
 * Adjusts the PPUs current sprite size. Set at the next NMI.
 * @param large 0: 8x8, 1: 8x16
 */
extern void __fastcall__ ppu_sprite_size(u8 large);
/**
 * Adjusts the PPUs current master/slave setting. Set at the next NMI.
 * @param master 0: read backdrop from EXT, 1: output color on EXT
 */
extern void __fastcall__ ppu_master(u8 master);
/**
 * Adjusts the PPUs current NMI setting. Happens immediately.
 * @param enable 0: off, 1: on
 */
extern void __fastcall__ ppu_nmi(u8 enable);
/**
 * Waits until the next VBlank NMI finishes, then returns
 */
extern void __fastcall__ ppu_wait_nmi(void);
/**
 * Sets the PPU Address register to the provided address.
 * @param addr the address to set
 */
extern void __fastcall__ ppu_set_addr(u16 addr);
/**
 * Writes the given data to the PPU at the current address.
 * @param data the data to write
 * @param size the length of the data to write
 */
extern void __fastcall__ ppu_write(const u8* data, u16 size);

extern const volatile u8 ZP_PPU_FRAME_CNT;
#pragma zpsym ("ZP_PPU_FRAME_CNT");
#endif //_NES_PPU_H_