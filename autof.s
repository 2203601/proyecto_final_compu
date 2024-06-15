// autof.s 
// 10 de Junio 2024
// Arqui I UCC

.text

.global autof

autof:
        PUSH {R4, R5, R6, LR}
        MOV R4, #15
        LDR R5, =array // load base address of array into R5
loop:   LDRB R6, [R5], #1
        MOV R0, R6
        BL disp_binary 
        MVN R0, R6 // interface outputs are active by low
        BL leds
        MOV R0, #300
        BL delayMillis
        SUBS R4, R4, #1
        BNE loop 
        POP {R4, R5, R6, PC} // return from autof

.data

array:

    .byte 0x80
    .byte 0x40
    .byte 0x10
    .byte 0x08
    .byte 0x04
    .byte 0x02
    .byte 0x01
    .byte 0x00   @ Agregué un byte extra para asegurar que se apaguen los LEDs al final
    .byte 0x01
    .byte 0x02
    .byte 0x04
    .byte 0x08
    .byte 0x10
    .byte 0x20
    .byte 0x40
        
