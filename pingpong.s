// pinpong.s 
// 17 de Junio 2024
// Arqui I UCC

.text

.global pingpong
.global SALIR
.global DELAY
.global DELAY_4
.global Delay

pingpong:
        PUSH {R4, R5, R6, R7, R9, R10, R11, LR}  // Guardar registros y el valor de retorno
       LDR R11, =DELAY_4
       LDR R6, [R11]
       LDR R9, = DELAY
       STR R6, [R9]
       LDR R10, = SALIR
        MOV R4, #28           // Establecer el contador de bucle a 12
        LDR R5, =array_pingpong  // Cargar la dirección base de la secuencia en R5
        
loop:   LDRB R6, [R5], #1     // Cargar un byte de la secuencia en R6 y avanzar el puntero
		LDR R7, [R10]
        CMP R7, #1
        BEQ break
        
        MOV R0, R6             // Mover el valor a R0 para pasar a disp_binary
        BL disp_binary         // Llamar a la función disp_binary
        MVN R0, R6             // Invertir los bits para que los LED se activen con nivel bajo
        BL leds                // Llamar a la función leds
		LDR R6, [R9]
        MOV R0, R6          // Establecer el retraso en 400 ms
        BL Delay         // Llamar a la función delayMillis
        SUBS R4, R4, #1        // Decrementar el contador de bucle
        BNE loop               // Si no ha llegado a cero, repetir el bucle
        
        MOV R4, #8
        LDR R5, =array_end // load base address of array into R5
        
loop2:   LDRB R6, [R5], #1
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
        BNE loop2 
        
break:
		STR R6, [R11]
		MOV R0, #0
		STR R0, [R10]
		POP {R4, R5, R6, R7, R9, R10, R11, PC} 
.data

array_pingpong:

    .byte 0x99  // 1001 1001
    .byte 0xD9  // 1101 1001
    .byte 0x9D  // 1001 1101
    .byte 0xD9  // 1101 1001
    .byte 0x9B  // 1001 1011
    .byte 0xB9  // 1011 1001
    .byte 0x9D  // 1001 1101
    .byte 0xD9  // 1101 1001
    .byte 0x9B  // 1001 1011
    .byte 0xB9  // 1011 1001
    .byte 0x9D  // 1001 1101
    .byte 0xD9  // 1101 1001
    .byte 0x9D  // 1001 1101
    .byte 0xD9  // 1101 1001
    .byte 0x9B  // 1001 1011
    .byte 0xB9  // 1011 1001
    .byte 0x9D  // 1001 1101
    .byte 0xD9  // 1101 1001
    .byte 0x9B  // 1001 1011
    .byte 0xB9  // 1011 1001
    .byte 0x9D  // 1001 1101
    .byte 0xD9  // 1101 1001
    .byte 0x9D  // 1001 1101
    .byte 0xD9  // 1101 1001
    .byte 0x9B  // 1001 1011
    .byte 0xB9  // 1011 1001
    .byte 0x9D  // 1001 1101
    .byte 0xD9  // 1101 1001
    .byte 0x9B  // 1001 1011
    .byte 0xB9  // 1011 1001
    .byte 0x9D  // 1001 1101
    .byte 0x9B  // 1001 1011
          
array_end: 
	.byte 0x80
	.byte 0x40
    .byte 0x20
    .byte 0x10
    .byte 0x08
    .byte 0x04
    .byte 0x02
    .byte 0x01
