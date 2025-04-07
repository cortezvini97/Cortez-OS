#include "kernel.h"

void main_kernel(){
    printf("Bem-vindo ao Cortez OS");
    for(int i = 0; i < 4; i++){
        sleep(100000000);
        printf(".");
    }
    setTimezone("America/Sao_Paulo");
    clearScreen();

    launch_shell(0, "Cortez OS");

    
}

void handle_user_input(){
    clearScreen();

    printf("Precione Enter para iniciar o Shell\n");
    printf("Precione 'a' para Desligar\n");
    printf("Precione 'b' para reiniciar");

    while (1)
    {
        if(inportb(0x64) & 0x1){
            switch (inportb(0x60))
            {
                case 28:
                    clearScreen();
                    launch_shell(0, "Cortez OS");
                    break;
                
                case 30:
                    clearScreen();
                    kernelShutdownApi();
                    break;
                case 48:
                    clearScreen();
                    kernelRebootApi();
                    break;
                break; 
            }
        }
    }
}


void kernelGetDateApi() {
    clearScreen();
    setCursorPosition(0, 0);
    setisUpdateCursor(0);
    printf("Precione Enter para Sair:\n\n");
    while (1) {
        DateTime dateTime = get_datetime(); 
        printf("\rData: %02d/%02d/20%02d | Hora: %02d:%02d:%02d",
            dateTime.day, dateTime.month, dateTime.year,
            dateTime.hour, dateTime.minute, dateTime.second);
        if(inportb(0x64) & 0x1){
            if(inportb(0x60) == 28){
                clearScreen();
                break;
            }
        }
    }
    setisUpdateCursor(1);
}

void kernelShutdownApi(){
    printf("Desligando o Sistema");
    for(int i = 0; i < 4; i++){
        sleep(100000000);
        printf(".");
    }
    shutdown();
}

void kernelRebootApi(){
    printf("Reiniciando o Sistema");
    for(int i = 0; i < 4; i++){
        sleep(100000000);
        printf(".");
    }
    reboot();
}