;Author: Steven Goldade
;Date: 11/8/2023

.section .nmi.1,"axR",@progbits
.global __nmi_update
jsr __nmi_update