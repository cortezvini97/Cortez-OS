#include "keyboard.h"

void main_kernel(){
    clearScreen();
    print("Welcome to Cortez OS\n");
    cursorX = 2;
    cursorY = 2;
    while (1)
    {
        print("\nCORTEZ> ");
        string ch = readStr();
        if(strEql(ch,"cmd"))
        {
            print("\nYou are allready in cmd\n");
        }else if(strEql(ch, "clear")){
            clearScreen();
        }else if(strEql(ch, "exit")){
            print("\nbye !");
            break;
        }else {
            print("\nBad command!\n");
        }
    }
    print("\n");
}