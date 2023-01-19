; Author: Steven Goldade
.import _main, copydata
.export __STARTUP__ : absolute = 1
.export reset

.importzp ZP_PPU_CTRL
.import PPU_CTRL, PPU_MASK, PPU_STATUS, PPU_DATA, PPU_ADDR
.import APU_DMC_FLAGS, APU_FRAME_COUNTER

.segment "VECTORS"
.import nmi, irq
.word nmi
.word reset
.word irq

.include "zeropage.inc" ; for compiler zero page info
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
    stx PPU_CTRL ; this is zero anyways?
    stx PPU_MASK ; this is also zero anyways?
    stx APU_DMC_FLAGS

ppu_init:
    bit PPU_STATUS ; clear vblank flag
@1:
    bit PPU_STATUS
    bpl @1 ; wait until a vblank (V goes to Plus)

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

ppu_wait:
    bit PPU_STATUS ; clear vblank flag
@1:
    bit PPU_STATUS
    bpl @1

    ; enable PPU NMI
    lda #$80
    sta ZP_PPU_CTRL
    sta PPU_CTRL

    jmp _main