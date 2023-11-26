;Author: Steven Goldade
;Date: 10/26/2023
.include "nespp/ppu.inc"

.text
.global __vram_buffer_length, __vram_buffer
.global __nmi_ppu_buffer_copy
__nmi_ppu_buffer_copy:
    ldx __vram_buffer_length
    beq .Lreturn
    ldx #$00
.Lread_prologue:
    ldy __vram_buffer, x
    inx
    lda __vram_buffer, x
    sta PPUADDR
    inx
    lda __vram_buffer, x
    sta PPUADDR
    inx
.Lbuffer_copy:
    lda __vram_buffer, x
    sta PPUDATA
    inx
    dey
    bne .Lbuffer_copy
    cpx __vram_buffer_length
    bcc .Lread_prologue
    sty __vram_buffer_length
.Lreturn:
    rts
