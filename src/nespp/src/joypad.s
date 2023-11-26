;Author: Steven Goldade
;Date : 11/8/2023
JOYPAD1 = $4016
JOYPAD2 = $4017

.global joypad_1_raw, joypad_2_raw, joypad_1_pressed, joypad_2_pressed, joypad_1_held, joypad_2_held, joypad_1_released, joypad_2_released

.text
.global __poll_joypad
__poll_joypad:
    ldx #00
    ldy #01
    sty joypad_1_raw ; This lets us use the carry bit chucking a 1 out at the end to end the loop
    sty JOYPAD1
    stx JOYPAD1
.Lread:
    lda JOYPAD2
    lsr
    rol joypad_2_raw
    lda JOYPAD1
    lsr
    rol joypad_1_raw
    bcc .Lread

    lda joypad_1_raw
    eor joypad_1_held
    and joypad_1_raw
    sta joypad_1_pressed
    lda joypad_2_raw
    eor joypad_2_held
    and joypad_2_raw
    sta joypad_2_pressed

    lda joypad_1_raw
    eor joypad_1_held
    and joypad_1_held
    sta joypad_1_released
    lda joypad_2_raw
    eor joypad_2_held
    and joypad_2_held
    sta joypad_2_released

    lda joypad_1_raw
    sta joypad_1_held
    lda joypad_2_raw
    sta joypad_2_held

    rts


