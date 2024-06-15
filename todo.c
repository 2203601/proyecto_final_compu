#include <stdio.h>
#include <stdlib.h>
#include "EasyPIO.h"  // Incluye tu biblioteca EasyPIO si es necesario

void choquef(void);
void autof(void);
void disp_binary(int);
void leds(int num);
void no_yet(void);
int menu(void);

const char led[] = {14, 15, 18, 23, 24, 25, 8, 7}; // Asegúrate de que esto esté definido si usas EasyPIO

int main() {
    pioInit();
    int i, j;
    for (i = 0; i < 8; i++) {
        pinMode(led[i], OUTPUT);
    }
    

    int choice;
    for (;;) {
        choice = menu();

        switch (choice) {
            case 1: 
                autof(); // Implementa esta función si es necesario
                break;

            case 2:
                choquef();
                break;

                case 3:
                break;

                case 4: 
                break;

            case 5:
                exit(0);
        }
    }

    return 0;
}

void no_yet(void) {
    printf("Funcion No implementada\n");
}


int menu(void) {
    int s, j;
    for (j = 0; j < 8; j++) {
        digitalWrite(led[j],0);
    }
    do {
        printf("MENU\n");
        printf("1) autof\n");
        printf("2) choquef\n");
        printf("3) opcion3\n");
        printf("4) opcion4\n");
        printf("5) Salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &s);
    } while (s < 1 || s > 5);

    return s;
}

void choquef(void) {
    printf("Mostrando choque:\n");
    unsigned char tabla[8] = {0x81, 0x42, 0x24, 0x10, 0x10, 0x24, 0x42, 0x81};
    for (int i = 0; i < 8; i++) {
        disp_binary(tabla[i]);
        leds(-tabla[i]);  // Descomenta esto si usas EasyPIO
        delayMillis(300);  // Descomenta esto si usas EasyPIO
    }
}

void disp_binary(int i) {
    for (int t = 128; t > 0; t = t / 2) {
        if (i & t)
            printf("*");
        else
            printf("_");
    }
    printf("\n");
}

void leds(int num) {
    int i, numval;
    for (i = 0; i < 8; i++) {
        numval = (num >> i) & 0x01;
        digitalWrite(led[i], numval);
    }
}


