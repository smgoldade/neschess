; Author: Steven Goldade
.global PPU_CTRL, PPU_MASK, PPU_STATUS, PPU_SCROLL, PPU_ADDR, PPU_DATA
.global NAMETABLE_0, ATTRIBUTE_TABLE_0, NAMETABLE_1, ATTRIBUTE_TABLE_1, NAMETABLE_2, ATTRIBUTE_TABLE_2, NAMETABLE_3, ATTRIBUTE_TABLE_3
.global BACKGROUND_PALETTE, SPRITE_PALETTE
.global OAM_ADDR, OAM_DATA, OAM_DMA

.global NT_BUFFER

.global _ppu_off, _ppu_on, _ppu_wait_nmi, _ppu_frame_count, _ppu_set_addr, ppu_wait
.global _ppu_write, _ppu_nmi_nt_update

.global _ppu_darken_color, _ppu_lighten_color, _ppu_darken_bg, _ppu_lighten_bg, _ppu_bg_palette, _ppu_spr_palette