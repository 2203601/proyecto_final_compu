#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>

#include "EasyPIO.h"  // Incluye tu biblioteca EasyPIO si es necesario

void* choquef(void* arg);
void disp_binary(int i);
void leds(int num);
void* autof(void* arg);
void* pingpong(void* arg);
void* cowboy(void* arg);
int menu(void);
void password(void);

#define QUIT_KEY 'q'
#define DELAY_INTERVAL 250
#define DEFAULT_DELAY 1000
#define KEY_UP 'u'
#define KEY_DOWN 'd'

unsigned int QUIT;
size_t DELAY;
size_t DELAY_1 = DEFAULT_DELAY;
size_t DELAY_2 = DEFAULT_DELAY;
size_t DELAY_3 = DEFAULT_DELAY;
size_t DELAY_4 = DEFAULT_DELAY;

void Delay(size_t a) {
    a = a * 100000;
    while (a--);
}
struct termios old_termios, new_termios;
// Configuración de la terminal para no bloquear la entrada del teclado
void set_terminal_mode()
{
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~ICANON; // Desactiva el modo canónico
    new_termios.c_lflag &= ~ECHO;   // Desactiva el eco
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void reset_terminal_mode()
{
   
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

int getch()
{
    int c;

    // Lee un carácter desde la entrada estándar
    c = getchar();

    return c;
}

void* KeyListener(void* arg)
{
    while (!QUIT)
    {
        int key = getch();
        if (key == QUIT_KEY)
            QUIT = 1;
        else if (key == KEY_UP)
        {
            if (DELAY - DELAY_INTERVAL != 0)
                DELAY -= DELAY_INTERVAL;
        }
        else if (key == KEY_DOWN)
        {
            DELAY += DELAY_INTERVAL;
        }
    }
    return NULL;
}

const unsigned char led[] = { 14, 15, 18, 23, 24, 1, 12, 16 }; // Asegúrate de que esto esté definido si usas EasyPIO

int main() {
    pioInit();
    int i, j;
    for (i = 0; i < 8; i++) {
        pinMode(led[i], OUTPUT);
    }
    
    password();
    printf("Contraseña Correcta!\n");

    int choice;
    for (;;) {
        choice = menu();
        pthread_t threads[2];

        switch (choice) {

        case 1:
            set_terminal_mode();  // Configurar la terminal
            DELAY = DELAY_1;
            pthread_create(&threads[0], NULL, KeyListener, NULL);
            pthread_create(&threads[1], NULL, autof, NULL);
            pthread_join(threads[0], NULL);
            pthread_join(threads[1], NULL);
            DELAY_1 = DELAY;
            reset_terminal_mode();           
             break;

        case 2:
            set_terminal_mode();  // Configurar la terminal
            DELAY = DELAY_2;
            pthread_create(&threads[0], NULL, KeyListener, NULL);
            pthread_create(&threads[1], NULL, choquef, NULL);
            pthread_join(threads[0], NULL);
            pthread_join(threads[1], NULL);
            DELAY_2 = DELAY;
            reset_terminal_mode();
            break;

        case 3:
            set_terminal_mode();  // Configurar la terminal
            DELAY = DELAY_3;
            pthread_create(&threads[0], NULL, KeyListener, NULL);
            pthread_create(&threads[1], NULL, cowboy, NULL);
            pthread_join(threads[0], NULL);
            pthread_join(threads[1], NULL);
            DELAY_3 = DELAY;
            reset_terminal_mode();            
            break;

        case 4:
             set_terminal_mode();  // Configurar la terminal
            DELAY = DELAY_4;
            pthread_create(&threads[0], NULL, KeyListener, NULL);
            pthread_create(&threads[1], NULL, pingpong, NULL);
            pthread_join(threads[0], NULL);
            pthread_join(threads[1], NULL);
            DELAY_4 = DELAY;
            reset_terminal_mode();            
            break;
            
        case 5:
            reset_terminal_mode();  // Restablecer la configuración de la terminal
            exit(0);
        }
    }

    return 0;
}

void password(void) {
    char password1[20]; // Declarar como array de caracteres
    int ver = 0;

    printf("Ingrese la Contraseña: \n");
    scanf("%s", password1); // Leer una cadena de caracteres

    do {
        if (strcmp(password1, "1234") == 0) { // Comparar cadenas con strcmp
            ver = 1;
        }
        else {
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
        digitalWrite(led[j], 0);
    }
    do {
        Delay(2000);
        disp_binary(0);
        printf("\033[H\033[J"); // Limpia la pantalla de la terminal
        printf("\033[?25h");
        QUIT = 0;
        DELAY = DEFAULT_DELAY;
        printf("MENU\n");
        printf("1) Autof\n");
        printf("2) Choquef\n");
        printf("3) Cowboys Duel\n");
        printf("4) Pingpong\n");
        printf("5) Salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &s);
    } while (s < 1 || s > 5);

    return s;
}

void* choquef(void* arg) {
    printf("\033[H\033[J"); // Limpia la pantalla de la terminal
    printf("Mostrando choque:\n");

    while (!QUIT) {
        unsigned char tabla[8] = { 0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81 };
        for (int i = 0; i < 8; i++) {
            if (QUIT) break;
            disp_binary(tabla[i]); // solo muestra en pantalla
            leds(~tabla[i]);  // Descomenta esto si usas EasyPIO
            Delay(DELAY);
        }
    }
    return NULL;
}

void* cowboy(void* arg) {
    printf("\033[H\033[J"); // Limpia la pantalla de la terminal
    printf("Mostrando cowboy duel:\n");

    unsigned char vaqueros[5] = { 0x18, 0x24, 0x42, 0x81, 0x82 }; // caminata de los vaqueros
    unsigned char disparo[6] = { 0x86, 0x8A, 0x92, 0xA2, 0xC2, 0x02 }; // disparo

    while(!QUIT){
            for (int j = 0; j < 5; j++) { // for para la caminata 
                if (QUIT) break;
                disp_binary(vaqueros[j]); // solo muestra en pantalla
                leds(~vaqueros[j]);  // Descomenta esto si usas EasyPIO
                    Delay(DELAY);
            }

            for (int i = 0; i < 6; i++) { // for para el disparo
                if (QUIT) break;
                disp_binary(disparo[i]); // solo muestra en pantalla
                leds(~disparo[i]);  // Descomenta esto si usas EasyPIO
                delayMillis(100);
                Delay(DELAY);


                if (i == 4) { // si el array del disparo llega al penultimo bit
                    if (QUIT) break;
                    disp_binary(disparo[i + 1]); // solo muestra en pantalla
                    leds(~disparo[i + 1]);  // Descomenta esto si usas EasyPIO
                    Delay(DELAY);
                }
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
        digitalWrite(led[i], !numval);
    }
}
