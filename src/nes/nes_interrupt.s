; Author: Steven Goldade
.export nmi, irq

.importzp ZP_PPU_CTRL, ZP_PPU_MASK, ZP_SCROLL_X, ZP_SCROLL_Y
.segment "CODE"

.import PPU_CTRL, PPU_MASK, PPU_SCROLL
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
    bne @copymem
    jmp @update_ppu

@copymem:

@update_ppu:
    lda ZP_SCROLL_X
    sta PPU_SCROLL
    lda ZP_SCROLL_Y
    sta PPU_SCROLL

    lda ZP_PPU_CTRL
    sta PPU_CTRL

    lda ZP_PPU_MASK
    sta PPU_MASK
    ;restore the registers
    pla
    tay
    pla
    tax
    pla
irq:
    rti