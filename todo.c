#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <pthread.h>
// #include <termios.h>
// #include <unistd.h>

//#include "EasyPIO.h"  // Incluye tu biblioteca EasyPIO si es necesario

void choquef(void);
void disp_binary(int);
void leds(int num);
//void autof(void);
//void pingpong (void);
void cowboy(void);
int menu(void);
void password(void);




const unsigned char led[] = {14, 15, 18, 23, 24, 1, 12, 16}; // Asegúrate de que esto esté definido si usas EasyPIO

int main() {
   // pioInit();
    int i, j;
    for (i = 0; i < 8; i++) {
       // pinMode(led[i], OUTPUT);
    }
    
        printf("Contraseña Correcta!\n");



    int choice;
    for (;;) {
        choice = menu();

        switch (choice) {
            case 1: 
             //  autof();

                break;

            case 2:
                choquef();
                break;

                case 3:
                cowboy();
                break;

                case 4: 
               // pingpong();
                break;

            case 5:
                exit(0);
        }
    }

    return 0;
}

void password (void){
    
   char password1[20]; // Declarar como array de caracteres
    int ver = 0;

    printf("Ingrese la Contraseña: \n");
    scanf("%s", password1); // Leer una cadena de caracteres

    do {
        if (strcmp(password1, "1234") == 0) { // Comparar cadenas con strcmp
            ver = 1;
            menu();
        } else {
            ver = 0;
            printf("Contraseña incorrecta. Intente de nuevo\n");
            printf("Ingrese la Contraseña: \n");
            scanf("%s", password1); // Leer de nuevo la contraseña
        }
    } while (ver != 1);
    
    
    
}


int menu(void) {
    int s, j;
    for (j = 0; j < 8; j++) {
       // digitalWrite(led[j],0);
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
    unsigned char tabla[8] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
    for (int i = 0; i < 8; i++) {
        disp_binary(tabla[i]); //solo muestra en pantalla
       // leds(~tabla[i]);  // Descomenta esto si usas EasyPIO
     //   delayMillis(700);  // Descomenta esto si usas EasyPIO
    }
}

void cowboy (void){
    
    printf("Mostrando choque:\n");
    
    // para saber cual es el bit,  se usa hexadecimal: por ej, 00011000, vemos que 0001 es 1 y 1000 es 8 entonces el bit es 0x18
    
    unsigned char vaqueros[5] = {0x18, 0x24, 0x42, 0x81, 0x82 }; // caminata de los vaqueros, uno de los vaqueros vuelve para atras pero es como si se diera vuelta
    unsigned char disparo[6] = {0x86, 0x8A, 0x92, 0xA2, 0xC2, 0x02}; // disparo, otro array porque debe ser más rápido, y se apaga uno de los leds es porque se muere uno
        
    for (int j = 0; j < 5; j++) { // for para la caminata 
        
            disp_binary(vaqueros[j]); //solo muestra en pantalla
           // leds(~vaqueros[j]);  // Descomenta esto si usas EasyPIO
           // delayMillis(700);  // Descomenta esto si usas EasyPIO
            
            
        }
        

    for (int i = 0; i < 6; i++) { // for para el disparo
        
        disp_binary(disparo[i]); //solo muestra en pantalla
        // leds(~disparo[i]);  // Descomenta esto si usas EasyPIO
       // delayMillis(100);  // Descomenta esto si usas EasyPIO
        
        if(i == 4){ // si el array del disparo llega al penultimo bit, que el bit que le sigue dure más para que se vea el vaquero que sobrevive
            
            disp_binary(disparo[i+1]); //solo muestra en pantalla
           // leds(~disparo[i+1]);  // Descomenta esto si usas EasyPIO
           // delayMillis(700); 
            
            
            }
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
      //  digitalWrite(led[i], !numval);
    }
}

