;Author: Steven Goldade
.include "nes_input.inc"
.include "nes_zeropage.inc"

INPUT_CONTROLLER_1 := $4016
INPUT_CONTROLLER_2 := $4017

.proc sample_controllers
    lda #$01
    sta INPUT_CONTROLLER_1
    sta ZP_CONTROLLER_1 ; Used so that we can detect when the 1 bit out to end the loop
    lsr
    sta INPUT_CONTROLLER_1
@1:
    lda INPUT_CONTROLLER_2
    lsr
    rol ZP_CONTROLLER_2
    lda INPUT_CONTROLLER_1
    lsr
    rol ZP_CONTROLLER_1
    bcc @1

    ; Any newly pressed buttons
    lda ZP_CONTROLLER_1
    eor ZP_C1_HELD
    and ZP_CONTROLLER_1
    sta ZP_C1_PRESSED
    lda ZP_CONTROLLER_2
    eor ZP_C2_HELD
    and ZP_CONTROLLER_2
    sta ZP_C2_PRESSED

    ; Any released buttons
    lda ZP_CONTROLLER_1
    eor ZP_C1_HELD
    and ZP_C1_HELD
    sta ZP_C1_RELEASED
    lda ZP_CONTROLLER_2
    eor ZP_C2_HELD
    and ZP_C2_HELD
    sta ZP_C2_RELEASED

    ; store current as held
    lda ZP_CONTROLLER_1
    sta ZP_C1_HELD
    lda ZP_CONTROLLER_2
    sta ZP_C2_HELD

    rts
.endproc

;u8 __fastcall__ input_c1_held();
.proc _input_c1_held
    lda ZP_C1_HELD
    rts
.endproc

;u8 __fastcall__ input_c1_pressed();
.proc _input_c1_pressed
    lda ZP_C1_PRESSED
    rts
.endproc

;u8 __fastcall__ input_c1_released();
.proc _input_c1_released
    lda ZP_C1_RELEASED
    rts
.endproc

;u8 __fastcall__ input_c2_held();
.proc _input_c2_held
    lda ZP_C2_HELD
    rts
.endproc

;u8 __fastcall__ input_c2_pressed();
.proc _input_c2_pressed
    lda ZP_C2_PRESSED
    rts
.endproc

;u8 __fastcall__ input_c2_released();
.proc _input_c2_released
    lda ZP_C2_RELEASED
    rts
.endproc

