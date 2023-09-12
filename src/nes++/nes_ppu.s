;Author: Steven Goldade

PPUCTRL = $2000
PPUMASK = $2001
PPUSTATUS = $2002
PPUSCROLL = $2005
PPUADDR = $2006
PPUDATA = $2007

.global buffered_control, buffered_mask, buffered_scroll_x, buffered_scroll_y
.global vram_buffer_length, vram_buffer
.global ppu_background_update
ppu_background_update:
    lda vram_buffer_length
    beq .Lend
    ldx #$00
.Lprologue:
    lda vram_buffer, x
    sta PPUADDR
    inx
    lda vram_buffer, x
    sta PPUADDR
    inx
    ldy vram_buffer, x
    inx
.Lbuffer_copy:
    lda vram_buffer, x
    sta PPUDATA
    inx
    dey
    bne .Lbuffer_copy
    cpx vram_buffer_length
    bcc .Lprologue
.Lend:
    lda #$00
    sta vram_buffer_length
    bit PPUSTATUS
    lda buffered_scroll_x
    sta PPUSCROLL
    lda buffered_scroll_y
    sta PPUSCROLL
    lda buffered_control
    sta PPUCTRL
    lda buffered_mask
    sta PPUMASK
    rts