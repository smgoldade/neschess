; Author: Steven Goldade
.include "nes_zeropage.inc"
.zeropage
ZP_PPU_CTRL: .res 1
ZP_PPU_MASK: .res 1
ZP_PTR: .res 2
ZP_LEN: .res 2
ZP_SCROLL_X: .res 1
ZP_SCROLL_Y: .res 1
ZP_PPU_FRAME_CNT: .res 1
ZP_PPU_BUF_LEN: .res 1

.export _ZP_PPU_FRAME_CNT = ZP_PPU_FRAME_CNT