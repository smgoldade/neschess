; Author: Steven Goldade
.global PPU_CTRL, PPU_MASK, PPU_STATUS, PPU_SCROLL, PPU_ADDR, PPU_DATA
.global NAMETABLE_0, ATTRIBUTE_TABLE_0, NAMETABLE_1, ATTRIBUTE_TABLE_1, NAMETABLE_2, ATTRIBUTE_TABLE_2, NAMETABLE_3, ATTRIBUTE_TABLE_3
.global BACKGROUND_PALETTE, SPRITE_PALETTE
.global OAM_ADDR, OAM_DATA, OAM_DMA

.global PPU_BUFFER
.global OAM_BUFFER

.global _ppu_off, _ppu_on, _ppu_rendering, _ppu_show_left, _ppu_emphasis, _ppu_grayscale
.global _ppu_scroll, _ppu_nametable, _ppu_pattern_table, _ppu_sprite_size, _ppu_master
.global _ppu_wait_nmi, ppu_wait
.global _ppu_set_addr, _ppu_write
.global _ppu_nmi_nt_update, _ppu_nmi_at_update

.global _ppu_darken_color, _ppu_lighten_color, _ppu_darken_bg, _ppu_lighten_bg, _ppu_nmi_bg_pal_update, _ppu_nmi_spr_pal_update