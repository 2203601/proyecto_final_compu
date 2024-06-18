// autof.s 
// 10 de Junio 2024
// Arqui I UCC

.text

.global autof 
.global SALIR
.global DELAY
.global DELAY_1
.global Delay

autof:
        PUSH {R4, R5, R6, R7, R9, R10, R11, LR}
        LDR R11, = DELAY_1
        LDR R6, [R11]
        LDR R9, =DELAY
        STR R6, [R9]
        LDR R10, = SALIR
        MOV R4, #32
        LDR R5, =array // load base address of array into R5
        
loop:   LDRB R6, [R5], #1
        LDR R7, [R10]
        CMP R7, #1
        BEQ break
        
        MOV R0, R6
        BL disp_binary 
        MVN R0, R6 // interface outputs are active by low
        BL leds
        LDR R6, [R9]
        MOV R0, R6
        BL Delay
        SUBS R4, R4, #1
        BNE loop 
        
break:
      STR R6, [R11]
      MOV R0, #0
      STR R0, [R10]  
        POP {R4, R5, R6, R7, R9, R10, R11,  PC} // return from autof

.data

array:

    .byte 0x80
    .byte 0x40
    .byte 0x20
    .byte 0x10
    .byte 0x08
    .byte 0x04
    .byte 0x02
    .byte 0x01
    .byte 0x01
    .byte 0x02
    .byte 0x04
    .byte 0x08
    .byte 0x10
    .byte 0x20
    .byte 0x40
    .byte 0x80
    .byte 0x80
    .byte 0x40
    .byte 0x20
    .byte 0x10
    .byte 0x08
    .byte 0x04
    .byte 0x02
    .byte 0x01
    .byte 0x01
    .byte 0x02
    .byte 0x04
    .byte 0x08
    .byte 0x10
    .byte 0x20
    .byte 0x40
    .byte 0x80
