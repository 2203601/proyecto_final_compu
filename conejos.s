// autof.s 
// 10 de Junio 2024
// Arqui I UCC


.text

.global conejos

conejos:
    PUSH(R4, R5, R6, LR)

loop:
.data:

array:

.byte 0x80
        .byte 0x40
        .byte 0x10
        .byte 0x08
        .byte 0x04
        .byte 0x02
        .byte 0x01
        .byte 0x02
        .byte 0x04
        .byte 0x08
        .byte 0x10
        .byte 0x20
        .byte 0x40
        .byte 0x80