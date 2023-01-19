; Author: Steven Goldade

;------------------------
; ZERO PAGE SETUP
;------------------------
.segment "ZEROPAGE"
.exportzp ZP_PPU_CTRL, ZP_PPU_MASK, ZP_PTR, ZP_LEN, ZP_SCROLL_X, ZP_SCROLL_Y
ZP_PPU_CTRL: .res 1
ZP_PPU_MASK: .res 1
ZP_PTR: .res 2
ZP_LEN: .res 2
ZP_SCROLL_X: .res 1
ZP_SCROLL_Y: .res 1

.segment "CODE"
.import popax
;------------------------
; PPU
;------------------------
.export PPU_CTRL, PPU_MASK, PPU_STATUS, PPU_SCROLL, PPU_ADDR, PPU_DATA
PPU_CTRL := $2000   ; V - VBlank NMI (0: off, 1: on)
                    ; P - PPU Master Slave (0: read from EXT, 1: output on EXT)
                    ; H - Sprite Size (0: 8x8 sprite, 1: 8x16 sprite)
                    ; B - Background Pattern Table Address (0: $0000, 1: $1000)
                    ; S - Sprite Pattern Table Address (0: $0000, 1: $1000)
                    ; I - VRAM Increment per R/W of PPU_DATA (0: 1, 1: $20)
                    ; NN - Base Name Table Address (0: $2000, 1: $2400, 2: $2800, 3: $2C00)
PPU_MASK := $2001   ; B - Emphasize blue
                    ; G - Emphasize green
                    ; R - Emphasize red
                    ; s - Show Sprites
                    ; b - Show Background
                    ; M - Show sprites in leftmost 8 pixels
                    ; m - Show background in leftmost 8 bixels
                    ; G - Grayscale
PPU_STATUS := $2002 ; V - vblank has started
                    ; S - Sprite 0 Hit
                    ; O - Sprite overflow
                    ; ..... - Open Bus

PPU_SCROLL := $2005
PPU_ADDR := $2006
PPU_DATA := $2007

.export NAMETABLE_0, NAMETABLE_1, NAMETABLE_2, NAMETABLE_3
.export ATTRIBUTE_TABLE_0, ATTRIBUTE_TABLE_1, ATTRIBUTE_TABLE_2, ATTRIBUTE_TABLE_3
NAMETABLE_0 := $2000
ATTRIBUTE_TABLE_0 := $23C0
NAMETABLE_1 := $2400
ATTRIBUTE_TABLE_1 := $27C0
NAMETABLE_2 := $2800
ATTRIBUTE_TABLE_2 := $2BC0
NAMETABLE_3 := $2C00
ATTRIBUTE_TABLE_3 := $2FC0

.export BACKGROUND_COLOR
BACKGROUND_COLOR := $3F00

.export BACKGROUND_PALETTE_0, BACKGROUND_PALETTE_1, BACKGROUND_PALETTE_2, BACKGROUND_PALETTE_3
BACKGROUND_PALETTE_0 := $3F01
BACKGROUND_PALETTE_1 := $3F05
BACKGROUND_PALETTE_2 := $3F09
BACKGROUND_PALETTE_3 := $3F0D

.export SPRITE_PALETTE_0, SPRITE_PALETTE_1, SPRITE_PALETTE_2, SPRITE_PALETTE_3

SPRITE_PALETTE_0 := $3F11
SPRITE_PALETTE_1 := $3F15
SPRITE_PALETTE_2 := $3F19
SPRITE_PALETTE_3 := $3F1D

;void __fastcall__ ppu_off();
.export _ppu_off
.proc _ppu_off
    lda ZP_PPU_MASK
    and #%11100111
    sta ZP_PPU_MASK
    rts
.endproc
;void __fastcall__ ppu_on();
.export _ppu_on
.proc _ppu_on
    lda ZP_PPU_MASK
    ora #%00011000
    sta ZP_PPU_MASK
    rts
.endproc

; void __fastcall__ ppu_set_addr(u16 addr);
.export _ppu_set_addr
.proc _ppu_set_addr
    stx PPU_ADDR
    sta PPU_ADDR
    rts
.endproc

; void __fastcall__ ppu_write(u8* data, u16 size);
.export _ppu_write
.proc _ppu_write
    sta <ZP_LEN
    stx <(ZP_LEN+1)
    jsr popax
    sta <ZP_PTR
    stx <(ZP_PTR+1)
    ldy #$00
@1:
    lda (ZP_PTR), y ; A = *PTR
    sta PPU_DATA    ; PPU_DATA = A
    inc <ZP_PTR     ; ++PTR_LO
    bne @2          ; IF PTR_LO == 0
    inc <(ZP_PTR+1) ;    ++PTR_HI
@2:
    dec <ZP_LEN     ; --LEN_LO
    bne @1          ; IF LEN_LO != 0 JMP @1
    cpy <(ZP_LEN+1) ; IF LEN_HI == 0
    bne @3          ;
    rts             ;    RETURN
@3:
    dec <(ZP_LEN+1) ; ELSE LEN_HI--
    jmp @1          ; JMP @1
.endproc
;--------------------------
; OAM
;--------------------------
.export OAM_ADDR, OAM_DATA, OAM_DMA
OAM_ADDR := $2003
OAM_DATA := $2004
OAM_DMA := $4014

;--------------------------
; APU
;--------------------------
.export APU_DMC_FLAGS, APU_FRAME_COUNTER
APU_DMC_FLAGS := $4010      ; I - Interrupt enabled
                            ; L - Loop Flag
                            ; ..
                            ; RRRR - Rate
APU_FRAME_COUNTER := $4017  ; M - Mode, 0 - 4 step, 1 - 5 step
                            ; I - Interrupt inhibit
                            ; ......