; Author: Steven Goldade
.include "nes_apu.inc"
.include "nes_interrupt.inc"
.include "nes_ppu.inc"
.include "nes_zeropage.inc"

.import _main, copydata
.export __STARTUP__ : absolute = 1
.export reset

.segment "VECTORS"
.word nmi
.word reset
.word irq

.import __STACK_START__,__STACK_SIZE__
.segment "STARTUP"
; This reset takes most of its ideas from NESdev's init
reset:
    sei
    cld
    lda #$40
    sta APU_FRAME_COUNTER ; Clear APU interrupt
    ldx #$FF
    txs
    inx
    stx APU_DMC_FLAGS

ppu_init:
    bit PPU_STATUS ; clear vblank flag if it was set on reset
    jsr ppu_wait

clear_palette:
    lda #$3f
    sta PPU_ADDR
    stx PPU_ADDR
    ldx #$20 ; 32 colors
    lda #$0f ; Black
@1:
    sta PPU_DATA
    dex
    bne @1

clear_ram:
    txa
@1:
    sta $0000, x
    sta $0100, x
    sta $0200, x
    sta $0300, x
    sta $0400, x
    sta $0500, x
    sta $0600, x
    sta $0700, x
    inx
    bne @1

clear_nametables:
    lda #$20
    sta PPU_ADDR
    stx PPU_ADDR
    txa
    ldy #$10
@1:
    sta PPU_DATA
    inx
    bne @1
    dey
    bne @1

    jsr copydata ; Compiler DATA section support
    ; Setup the Compiler Stack
    lda #<(__STACK_START__ + __STACK_SIZE__)
    ldx #>(__STACK_START__ + __STACK_SIZE__)
    sta sp
    stx sp+1

    jsr ppu_wait

    ; enable PPU NMI
    lda #$80
    sta ZP_PPU_CTRL
    sta PPU_CTRL

    jmp _main