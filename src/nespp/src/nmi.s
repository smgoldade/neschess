;Author: Steven Goldade
;Date: 11/8/2023

.section .nmi_begin,"axG",@progbits,nmi
.global nmi
nmi:
    pha
    txa
    pha
    tya
    pha
    lda __rc2
    pha
    lda __rc3
    pha
    lda __rc4
    pha
    lda __rc5
    pha
    lda __rc6
    pha
    lda __rc7
    pha
    lda __rc8
    pha
    lda __rc9
    pha
    lda __rc10
    pha
    lda __rc11
    pha
    lda __rc12
    pha
    lda __rc13
    pha
    lda __rc14
    pha
    lda __rc15
    pha
    lda __rc16
    pha
    lda __rc17
    pha
    lda __rc18
    pha
    lda __rc19
    pha

.section .nmi_end, "axG", @progbits,nmi
    pla
    sta __rc19
    pla
    sta __rc18
    pla
    sta __rc17
    pla
    sta __rc16
    pla
    sta __rc15
    pla
    sta __rc14
    pla
    sta __rc13
    pla
    sta __rc12
    pla
    sta __rc11
    pla
    sta __rc10
    pla
    sta __rc9
    pla
    sta __rc8
    pla
    sta __rc7
    pla
    sta __rc6
    pla
    sta __rc5
    pla
    sta __rc4
    pla
    sta __rc3
    pla
    sta __rc2
    pla
    tay
    pla
    tax
    pla
    rti

.section .nmi.1,"axR",@progbits
.global __nmi_update
jsr __nmi_update