; Author: Steven Goldade
.include "nes_interrupt.inc"
.include "nes_ppu.inc"
.include "nes_zeropage.inc"

.code
nmi:
    ; store the registers
    pha
    txa
    pha
    tya
    pha

    ; check if we're rendering, if not we dont update PPU memory
    lda ZP_PPU_MASK
    and #%00011000 ; show sprites or show background
    bne @update_bg_palette
    jmp @update_ppu

@update_bg_palette:
    lda ZP_PPU_UPDATE
    and #%00000001
    beq @update_spr_palette
    lda #ZP_BG_PALETTE
    sta ZP_PTR
    lda #<BACKGROUND_PALETTE
    ldx #>BACKGROUND_PALETTE
    jsr palette_copy

@update_spr_palette:
    lda ZP_PPU_UPDATE
    and #%00000010
    beq @update_nametable
    lda #ZP_SPR_PALETTE
    sta ZP_PTR
    lda #<SPRITE_PALETTE
    ldx #>SPRITE_PALETTE
    jsr palette_copy

@update_nametable:

    lda #$00
    sta ZP_PPU_UPDATE
@update_ppu:
    lda ZP_SCROLL_X
    sta PPU_SCROLL
    lda ZP_SCROLL_Y
    sta PPU_SCROLL

    lda ZP_PPU_CTRL
    sta PPU_CTRL

    lda ZP_PPU_MASK
    sta PPU_MASK

    inc ZP_FRAME_CNT
    ;restore the registers
    pla
    tay
    pla
    tax
    pla
irq:
    rti

; A: low byte palette address
; X: hi byte palette address
; ZP_PTR: addr for palette
.proc palette_copy
    jsr _ppu_set_addr
    ldx ZP_PTR
    ldy #$0F
@1:
    lda $00, x
    sta PPU_DATA
    inx
    dey
    bpl @1
    rts
.endproc