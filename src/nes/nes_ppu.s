; Author: Steven Goldade
.include "nes_ppu.inc"
.include "nes_zeropage.inc"

PPU_CTRL = $2000    ; V - VBlank NMI (0: off, 1: on)
                    ; P - PPU Master Slave (0: read from EXT, 1: output on EXT)
                    ; H - Sprite Size (0: 8x8 sprite, 1: 8x16 sprite)
                    ; B - Background Pattern Table Address (0: $0000, 1: $1000)
                    ; S - Sprite Pattern Table Address (0: $0000, 1: $1000)
                    ; I - VRAM Increment per R/W of PPU_DATA (0: 1, 1: $20)
                    ; NN - Base Name Table Address (0: $2000, 1: $2400, 2: $2800, 3: $2C00)
PPU_MASK = $2001    ; B - Emphasize blue
                    ; G - Emphasize green
                    ; R - Emphasize red
                    ; s - Show Sprites
                    ; b - Show Background
                    ; M - Show sprites in leftmost 8 pixels
                    ; m - Show background in leftmost 8 bixels
                    ; G - Grayscale
PPU_STATUS = $2002  ; V - vblank has started
                    ; S - Sprite 0 Hit
                    ; O - Sprite overflow
                    ; ..... - Open Bus

PPU_SCROLL = $2005
PPU_ADDR = $2006
PPU_DATA = $2007

NAMETABLE_0 = $2000
.export _NAMETABLE_0 = NAMETABLE_0
ATTRIBUTE_TABLE_0 = $23C0
.export _ATTRIBUTE_TABLE_0 = ATTRIBUTE_TABLE_0
NAMETABLE_1 = $2400
.export _NAMETABLE_1 = NAMETABLE_1
ATTRIBUTE_TABLE_1 = $27C0
.export _ATTRIBUTE_TABLE_1 = ATTRIBUTE_TABLE_1
NAMETABLE_2 = $2800
.export _NAMETABLE_2 = NAMETABLE_2
ATTRIBUTE_TABLE_2 = $2BC0
.export _ATTRIBUTE_TABLE_2 = ATTRIBUTE_TABLE_2
NAMETABLE_3 = $2C00
.export _NAMETABLE_3 = NAMETABLE_3
ATTRIBUTE_TABLE_3 = $2FC0
.export _ATTRIBUTE_TABLE_3 := ATTRIBUTE_TABLE_3

PPU_BUFFER = $0700

BACKGROUND_PALETTE = $3F00
SPRITE_PALETTE := $3F10

.code
;void __fastcall__ ppu_off();
.proc _ppu_off
    lda ZP_PPU_MASK
    and #%11100111
    sta ZP_PPU_MASK
    jmp _ppu_wait_nmi
.endproc

;void __fastcall__ ppu_on();
.proc _ppu_on
    lda ZP_PPU_MASK
    ora #%00011000
    sta ZP_PPU_MASK
    jmp _ppu_wait_nmi
.endproc

;void __fastcall__ ppu_rendering(u8 background, u8 sprite);
.import popa
.proc _ppu_rendering
    and #$01
    beq @clr_sprite
    lda ZP_PPU_MASK
    ora #%00010000
    jmp @test_background
@clr_sprite:
    lda ZP_PPU_MASK
    and #%11101111
@test_background:
    sta ZP_PPU_MASK
    jsr popa
    and #$01
    beq @clr_background
    lda ZP_PPU_MASK
    ora #%00001000
    jmp @end
@clr_background:
    lda ZP_PPU_MASK
    and #%11110111
@end:
    sta ZP_PPU_MASK
    jmp _ppu_wait_nmi
.endproc

;void __fastcall__ ppu_show_left(u8 background, u8 sprite);
.import popa
.proc _ppu_show_left
    and #$01
    beq @clr_sprite
    lda ZP_PPU_MASK
    ora #%00000100
    jmp @test_background
@clr_sprite:
    lda ZP_PPU_MASK
    and #%11111011
@test_background:
    sta ZP_PPU_MASK
    jsr popa
    and #$01
    beq @clr_background
    lda ZP_PPU_MASK
    ora #%00000010
    jmp @end
@clr_background:
    lda ZP_PPU_MASK
    and #%11111101
@end:
    sta ZP_PPU_MASK
    rts
.endproc

;void __fastcall__ ppu_emphasis(u8 red, u8 green, u8 blue);
.import popax
.proc _ppu_emphasis
    and #$01
    beq @clr_blue
    lda ZP_PPU_MASK
    ora #%10000000
    jmp @test_green
@clr_blue:
    lda ZP_PPU_MASK
    and #%01111111
@test_green:
    sta ZP_PPU_MASK
    jsr popax
    and #$01
    beq @clr_green
    lda ZP_PPU_MASK
    ora #%01000000
    jmp @test_red
@clr_green:
    lda ZP_PPU_MASK
    and #%10111111
@test_red:
    sta ZP_PPU_MASK
    txa
    and #$01
    beq @clr_red
    lda ZP_PPU_MASK
    ora #%00100000
    jmp @end
@clr_red:
    lda ZP_PPU_MASK
    and #%11011111
@end:
    sta ZP_PPU_MASK
    rts
.endproc

;void __fastcall__ ppu_grayscale(u8 enable);
.proc _ppu_grayscale
    and #$01
    beq @clr_grayscale
    lda ZP_PPU_MASK
    ora #%00000001
    jmp @end
@clr_grayscale:
    lda ZP_PPU_MASK
    and #%11111110
@end:
    sta ZP_PPU_MASK
    rts
.endproc

;void __fastcall__ ppu_scroll(u8 x, u8 y);
.import popa
.proc _ppu_scroll
    sta ZP_SCROLL_Y
    jsr popa
    sta ZP_SCROLL_X
    rts
.endproc

;void __fastcall__ ppu_nametable(u8 nametable);
.proc _ppu_nametable
    and #$03
    tax
    lda ZP_PPU_CTRL
    and #%11111100
    sta ZP_PPU_CTRL
    txa
    ora ZP_PPU_CTRL
    sta ZP_PPU_CTRL
    rts
.endproc

;void __fastcall__ ppu_pattern_table(u8 background, u8 sprite);
.import popa
.proc _ppu_pattern_table
    and #$01
    beq @clr_sprite
    lda ZP_PPU_CTRL
    ora #%00001000
    jmp @test_bg
@clr_sprite:
    lda ZP_PPU_CTRL
    and #%1110111
@test_bg:
    sta ZP_PPU_CTRL
    jsr popa
    and #$01
    beq @clr_bg
    lda ZP_PPU_CTRL
    ora #%00010000
    jmp @end
@clr_bg:
    lda ZP_PPU_CTRL
    and #%11101111
@end:
    sta ZP_PPU_CTRL
    rts
.endproc

;void __fastcall__ ppu_sprite_size(u8 large);
.proc _ppu_sprite_size
    and #$01
    beq @clr
    lda ZP_PPU_CTRL
    ora #%00100000
    jmp @end
@clr:
    lda ZP_PPU_CTRL
    and #%11011111
@end:
    sta ZP_PPU_CTRL
    rts
.endproc

;void __fastcall__ ppu_master(u8 master);
.proc _ppu_master
    and #$01
    beq @clr
    lda ZP_PPU_CTRL
    ora #%01000000
    jmp @end
@clr:
    lda ZP_PPU_CTRL
    and #%10111111
@end:
    sta ZP_PPU_CTRL
    rts
.endproc

;void __fastcall__ ppu_nmi(u8 enable);
.proc _ppu_nmi
    and #$01
    beq @clr
    lda ZP_PPU_CTRL
    ora #%10000000
    jmp @end
@clr:
    lda ZP_PPU_CTRL
    and #%01111111
@end:
    sta ZP_PPU_CTRL
    sta PPU_CTRL
    rts
.endproc

;void __fastcall__ ppu_wait_nmi(void);
.proc _ppu_wait_nmi
    lda ZP_PPU_FRAME_CNT
    cmp ZP_LAST_FRAME
    beq @1
    inc ZP_LAG_COUNT
@1:
    cmp ZP_PPU_FRAME_CNT ;ZP_PPU_FRAME_CNT incremented at the end of NMI, once it changes we know the NMI happened
    beq @1
    lda ZP_PPU_FRAME_CNT
    sta ZP_LAST_FRAME
    rts
.endproc

; void __fastcall__ ppu_set_addr(u16 addr);
.proc _ppu_set_addr
    stx PPU_ADDR
    sta PPU_ADDR
    rts
.endproc

.proc ppu_wait
    bit PPU_STATUS
    bpl ppu_wait
    rts
.endproc

; void __fastcall__ ppu_write(const u8* data, u16 size);
.import popax
.proc _ppu_write
    sta ZP_LEN
    stx ZP_LEN+1
    jsr popax
    sta ZP_PTR
    stx ZP_PTR+1
    ldy #$00
@1:
    lda (ZP_PTR),y  ; A = *PTR
    sta PPU_DATA    ; PPU_DATA = A
    inc ZP_PTR      ; ++PTR_LO
    bne @2          ; IF PTR_LO == 0
    inc ZP_PTR+1    ;    ++PTR_HI
@2:
    dec ZP_LEN      ; --LEN_LO
    bne @1          ; IF LEN_LO != 0 JMP @1
    cpy ZP_LEN+1    ; IF LEN_HI == 0
    bne @3          ;
    rts             ;    RETURN
@3:
    dec ZP_LEN+1    ; ELSE LEN_HI--
    jmp @1          ; JMP @1
.endproc

; void __fastcall__ ppu_nmi_nt_update(const u8* data, u8 size, u8 nametable, u8 x, u8 y);
.import popa
.proc _ppu_nmi_nt_update
    ldx #$00
    stx ZP_PTR+1
    asl
    asl
    asl
    asl                     ; Max Y of 29 means first 3 shifts cant roll into the high byte, but next 2 can!
    rol ZP_PTR+1            ; This has a net effect of (y & 0x1F) << 5
    asl
    sta ZP_PTR
    rol ZP_PTR+1            ; ZP_PTR = Y*32
    jsr popax
    adc ZP_PTR
    sta ZP_PTR              ; ZP_PTR = Y*32 + X
    txa
    asl
    asl
    clc
    adc ZP_PTR+1
    adc #>NAMETABLE_0
    jmp nt_copy_ppu_buffer
.endproc

; void __fastcall__ ppu_nmi_at_update(const u8* data, u8 size, u8 attribute_table, u8 x, u8 y);
.import popa
.proc _ppu_nmi_at_update
    asl
    asl
    asl
    sta ZP_PTR          ; ZP_PTR = Y*8
    jsr popax
    clc
    adc ZP_PTR
    adc #<ATTRIBUTE_TABLE_0
    sta ZP_PTR          ; ZP_PTR = Y*8+X+attribute table low(0xC0)
    txa
    asl
    asl
    clc
    adc #>ATTRIBUTE_TABLE_0
    jmp nt_copy_ppu_buffer
.endproc

; Shared nametable copy logic
; A = Destination High Byte
; <ZP_PTR = Destination Low Byte
; C Stack: SRC_LEN SRC_LO SRC_HI
.proc nt_copy_ppu_buffer
    ldy ZP_PPU_BUF_LEN
    sta PPU_BUFFER,y    ; PPU_BUFFER = DEST_HI
    iny
    lda ZP_PTR
    sta PPU_BUFFER,y    ; PPU_BUFFER = DEST_HI DEST_LO
    iny
    sty ZP_PPU_BUF_LEN
    jsr popax
    ldy ZP_PPU_BUF_LEN
    sta ZP_LEN
    sta PPU_BUFFER,y    ; PPU_BUFFER = DEST_HI DEST_LO SRC_LEN
    iny
    sty ZP_PPU_BUF_LEN
    stx ZP_PTR          ; <ZP_PTR = SRC_LO
    jsr popa
    sta ZP_PTR+1        ; ZP_PTR = SRC
    ldy ZP_LEN
    tya
    clc
    adc ZP_PPU_BUF_LEN
    sta ZP_PPU_BUF_LEN  ; ZP_PPU_BUF_LEN = indexof PPU_BUFFER last data byte
    tax
    jmp copy_ppu_buffer
.endproc

; Y = SRC_LEN
; X = indexof PPU_BUFFER last data byte
; ZP_PTR = SRC
.proc copy_ppu_buffer
    lda (ZP_PTR),y
    sta PPU_BUFFER,x
    dex
    dey
    bpl copy_ppu_buffer
    rts
.endproc

.rodata
; defines one step darker for each palette color
DARKEN_COLORS:  .byte $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F, $0F
                .byte $00, $01, $02, $03, $04, $05, $06, $07, $08, $09, $0A, $0B, $0C, $0F, $0F, $0F
                .byte $10, $11, $12, $13, $14, $15, $16, $17, $18, $19, $1A, $1B, $1C, $0F, $0F, $0F
                .byte $20, $21, $22, $23, $24, $25, $26, $27, $28, $29, $2A, $2B, $2C, $2D, $0F, $0F
; defines one step lighter for each palette color
LIGHTEN_COLORS: .byte $10, $11, $12, $13, $14, $15, $16, $17, $18, $19, $1A, $1B, $1C, $2D, $2D, $2D
                .byte $20, $21, $22, $23, $24, $25, $26, $27, $28, $29, $2A, $2B, $2C, $2D, $2D, $2D
                .byte $30, $31, $32, $33, $34, $35, $36, $37, $38, $39, $3A, $3B, $3C, $3D, $2D, $2D
                .byte $30, $30, $30, $30, $30, $30, $30, $30, $30, $30, $30, $30, $30, $30, $2D, $2D

.code
;nes_color __fastcall__ ppu_darken_color(nes_color color)
.proc _ppu_darken_color
    tax
    lda DARKEN_COLORS,x
    rts
.endproc

;nes_color __fastcall__ ppu_lighten_color(nes_color color)
.proc _ppu_lighten_color
    tax
    lda LIGHTEN_COLORS,x
    rts
.endproc

;void __fastcall__ ppu_nmi_bg_pal_update(const nes_palette* data);
.proc _ppu_nmi_bg_pal_update
    sta ZP_PTR
    stx ZP_PTR+1
    ldy ZP_PPU_BUF_LEN
    lda #>BACKGROUND_PALETTE
    ldx #<BACKGROUND_PALETTE
    jmp pal_copy_ppu_buffer
.endproc

;void __fastcall__ ppu_nmi_spr_pal_update(const nes_palette* data);
.proc _ppu_nmi_spr_pal_update
    sta ZP_PTR
    stx ZP_PTR+1
    ldy ZP_PPU_BUF_LEN
    lda #>SPRITE_PALETTE
    ldx #<SPRITE_PALETTE
    jmp pal_copy_ppu_buffer
.endproc

; A = PAL_HI
; X = PAL_LO
.proc pal_copy_ppu_buffer
    sta PPU_BUFFER,y
    iny
    txa
    sta PPU_BUFFER,y
    iny
    lda #$10
    sta PPU_BUFFER, y
    iny
    tya
    clc
    adc #$10
    tax
    stx ZP_PPU_BUF_LEN
    ldy #$10
    jmp copy_ppu_buffer
.endproc

;--------------------------
; OAM
;--------------------------
OAM_ADDR := $2003
OAM_DATA := $2004
OAM_DMA := $4014

OAM_BUFFER := $0200
.export _sprites := OAM_BUFFER