; Author: Steven Goldade
.include "nes_apu.inc"

;--------------------------
; APU
;--------------------------
APU_DMC_FLAGS := $4010      ; I - Interrupt enabled
                            ; L - Loop Flag
                            ; ..
                            ; RRRR - Rate
APU_FRAME_COUNTER := $4017  ; M - Mode, 0 - 4 step, 1 - 5 step
                            ; I - Interrupt inhibit
                            ; ......