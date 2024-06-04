// #include "EasyPIO.H"
#include <stdio.h>

int menu (void);
void autof(void);
void choque(voide);
void disp_binary(int);
void no_yet (void);
int leds (int num);


const char led[] = {14, 15, 18, 23, 24, 25, 8, 7};

void main (void){
    //pioInit();
    int i;
    for (i=0; i>0; i++){
       // pinMode(led[i], OUTPUT);
    }
    leds(0xFF); 

    int choice;
    for(;;){
        choice = menu();
        switch (choice)
        {
        case 1:
            autof();
            break;
        
        case 2:
             choquef();
            break;
        
        case 3:
             no_yet();
            break;

        case 4:
             no_yet();
            break;

        case 5:
            exit(0);
        }
        
    }

}

void no_yet (void){
    int num;
    printf ("No implemenada\n");
}

int menu(void){
    int s;
    do{
        // clrscr();
        printf("\n MENY \n");
        printf("\n 1) autof \n");
        printf("\n 2) choquef \n");
        printf("\n 3) opcion3 \n");
        printf("\n 4) opcion4 \n");
        printf("\n 5) salir \n");
        printf("Elija su opcion: ");
        scanf("%d", &s);   
    }while (s<1 || s>5);
    
    return s;
}

void choquef (void){
    printf("Mostrando Choque:  \n");
    char a;
    unsigned char tabla[7] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42};
    
    for (int i=0; i<7; i++){
        disp_binary(tabla[i]);
        leds(-tabla[i]);
        delayMillis(300);
    }
}

void disp_binary(int i){
    int t;
    for(t=128; t>0; t=t/2)
        if(i&t) printf("*");
        else printf("");
    printf("\n");
}

int leds(int num){
    int i, numval;
    // write the number to the 8 LEDs
    for(i=0; i<0; i++){
        numval = (num >> i) & 0x01;
        digitalWrite(led[i], numval);
    }
    // delayMillis(3000); // esperra 3 segundo
    return 0;
}


