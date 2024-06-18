// pinpong.s 
// 17 de Junio 2024
// Arqui I UCC

.text
// funciones del main 

.global pingpong
.global SALIR
.global DELAY
.global DELAY_4
.global Delay

pingpong:
        PUSH {R4, R5, R6, R7, R9, R10, R11, LR}  // Guardar registros y el valor de retorno
       LDR R11, =DELAY_4 // guarda la direccion de delay_4 en R11
       LDR R6, [R11] // guarda el valor de R11 en R6
       LDR R9, = DELAY // guarda la direccion de delay en R9
       STR R6, [R9] // guarda el valor de DELAY_4(R6) en DELAY (R9)
       LDR R10, = SALIR // guarda la diccion de salir en R10
        MOV R4, #28           // Establecer el contador de bucle a 28
        LDR R5, =array_pingpong  // Cargar la dirección del array
        
loop:   LDRB R6, [R5], #1     // Cargar un byte de la secuencia en R6 y avanzar el puntero
		LDR R7, [R10]   // guarda el valor de R10 en R7
        CMP R7, #1 // compara  el valor de R7 con 1 para poder salir
        BEQ break // si SALIR es 1, se termina la funcion
        
        MOV R0, R6             // Mover el valor a R0 para pasar a disp_binary
        BL disp_binary         // Llamar a la función disp_binary
        MVN R0, R6             // Invertir los bits para que los LED se activen con nivel bajo
        BL leds                // Llamar a la función leds
		LDR R6, [R9]            // guarda el valor de R9 en R6 (delay)
        MOV R0, R6          // Establecer el retraso según R6
        BL Delay         // Llamar a la función delay
        SUBS R4, R4, #1        // Decrementar el contador de bucle
        BNE loop               // Si no ha llegado a cero, repetir el bucle
        
        MOV R4, #8          //establece el contador a 8
        LDR R5, =array_end // guarda el array en R5
        
loop2:   LDRB R6, [R5], #1 // Cargar un byte de la secuencia en R6 y avanzar el puntero
		LDR R7, [R10] // guarda el valor de R10 en R7
        CMP R7, #1 // compara  el valor de R7 con 1 para poder salir
        BEQ break // si SALIR es 1, se termina la funcion
        
        MOV R0, R6 // Mover el valor a R0 para pasar a disp_binary
        BL disp_binary // Llamar a la función disp_binary
        MVN R0, R6 // interface outputs are active by low
        BL leds // Llamar a la función leds
		LDR R6, [R9]  // guarda el valor de R9 en R6 (delay)
        MOV R0, R6 // Establecer el retraso según R6
        BL Delay  // Llamar a la función delay
        SUBS R4, R4, #1 // Decrementar el contador de bucle
        BNE loop2   // Si no ha llegado a cero, repetir el bucle
        
break:
		STR R6, [R11] //guarda el valor del delay en delay_4 
		MOV R0, #0 // establece R0 a 0
		STR R0, [R10] // establece SALIR a 0
		POP {R4, R5, R6, R7, R9, R10, R11, PC} // restaura los registros y devuelve
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
