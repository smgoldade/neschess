; Author: Steven Goldade
; ---------------------------------------------
; Some of these no doubt exist in the compiler,
; but I'm a bit of a masochist and like no
; hidden functions to be imported as much as
; possible.
;

; Needed for compiler ASM/C interfaces
.include "zeropage.inc"

.segment "CODE"

; Clears a page of memory.
; ZP $01 = page
; Modifies A, Y, $00
.export clear_page
.proc clear_page
    lda #$00
    ldy #$00
@1: sta ($00), Y
    iny
    bne @1
    rts
.endproc