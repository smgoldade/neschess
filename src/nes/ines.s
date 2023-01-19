; Author: Steven Goldade

INES_MAPPER = 0
INES_MIRROR = 0
INES_SRAM = 0

.segment "HEADER"

.byte "NES", $1A ; ID
.byte $02 ; 2 PRG Bank Count
.byte $01 ; 1 CHR Bank Count
.byte INES_MIRROR | (INES_SRAM << 1) | ((INES_MAPPER & $F) << 4)
.byte (INES_MAPPER & $F0)
.res 8, 0 ; Padding

.segment "CHARS"
.incbin "../chrrom.chr"