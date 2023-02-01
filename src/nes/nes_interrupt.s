; Author: Steven Goldade
.include "nes_input.inc"
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
    bne @update_ppu_mem
    jmp @sample_controllers

@update_ppu_mem:
    lda ZP_PPU_BUF_LEN
    beq @update_sprites
    jsr ppu_memory_copy
    lda #$00
    sta ZP_PPU_BUF_LEN

@update_sprites:
    lda #>OAM_BUFFER
    sta OAM_DMA

@sample_controllers:
    jsr sample_controllers

@update_ppu:
    bit PPU_STATUS
    lda ZP_SCROLL_X
    sta PPU_SCROLL
    lda ZP_SCROLL_Y
    sta PPU_SCROLL

    lda ZP_PPU_CTRL
    sta PPU_CTRL

    lda ZP_PPU_MASK
    sta PPU_MASK

    inc ZP_PPU_FRAME_CNT
    ;restore the registers
    pla
    tay
    pla
    tax
    pla
irq:
    rti

.proc ppu_memory_copy
    ldx #$00
@strt:
    lda PPU_BUFFER,x
    sta PPU_ADDR
    inx
    lda PPU_BUFFER,x
    sta PPU_ADDR
    inx
    ldy PPU_BUFFER,x
    inx
@cpy_buf:
    lda PPU_BUFFER,x
    sta PPU_DATA
    inx
    dey
    bne @cpy_buf
    cpx ZP_PPU_BUF_LEN
    bcc @strt
    rts
.endproc

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