#include "keyboard64.h"

uint8 keyboardcall() {
    char buff;
    string buffstr = (string) malloc(200);
    uint8 i = 0;
    uint8 reading = 1;
    uint8 shift = 0;

    int line = 0;

    while (reading) {
        if (inportb(0x64) & 0x1) {
            uint8 scancode = inportb(KEYBOARD_PORT);
            switch (scancode) {
                case 42: // Left Shift Pressed
                case 54: // Right Shift Pressed
                    shift = 1;
                    break;
                case 170: // Left Shift Released
                case 182: // Right Shift Released
                    shift = 0;
                    break;
                case 14: // Backspace
                    if (i > 0) {
                        i--; 
                        printc('\b'); // Move cursor para trás
                        printc(' ');  // Apaga o caractere visualmente
                        printc('\b'); // Move o cursor para trás de novo
                        buffstr[i] = 0; // Remove caractere do buffer
                    }
                    break;
                case 2: printc(shift ? '!' : '1'); buffstr[i++] = shift ? '!' : '1'; break;
                case 3: printc(shift ? '@' : '2'); buffstr[i++] = shift ? '@' : '2'; break;
                case 4: printc(shift ? '#' : '3'); buffstr[i++] = shift ? '#' : '3'; break;
                case 5: printc(shift ? '$' : '4'); buffstr[i++] = shift ? '$' : '4'; break;
                case 6: printc(shift ? '%' : '5'); buffstr[i++] = shift ? '%' : '5'; break;
                case 7: printc(shift ? '^' : '6'); buffstr[i++] = shift ? '^' : '6'; break;
                case 8: printc(shift ? '&' : '7'); buffstr[i++] = shift ? '&' : '7'; break;
                case 9: printc(shift ? '*' : '8'); buffstr[i++] = shift ? '*' : '8'; break;
                case 10: printc(shift ? '(' : '9'); buffstr[i++] = shift ? '(' : '9'; break;
                case 11: printc(shift ? ')' : '0'); buffstr[i++] = shift ? ')' : '0'; break;
                case 12: printc(shift ? '_' : '-'); buffstr[i++] = shift ? '_' : '-'; break;
                case 16: printc(shift ? 'Q' : 'q'); buffstr[i++] = shift ? 'Q' : 'q'; break;
                case 17: printc(shift ? 'W' : 'w'); buffstr[i++] = shift ? 'W' : 'w'; break;
                case 18: printc(shift ? 'E' : 'e'); buffstr[i++] = shift ? 'E' : 'e'; break;
                case 19: printc(shift ? 'R' : 'r'); buffstr[i++] = shift ? 'R' : 'r'; break;
                case 20: printc(shift ? 'T' : 't'); buffstr[i++] = shift ? 'T' : 't'; break;
                case 21: printc(shift ? 'Y' : 'y'); buffstr[i++] = shift ? 'Y' : 'y'; break;
                case 22: printc(shift ? 'U' : 'u'); buffstr[i++] = shift ? 'U' : 'u'; break;
                case 23: printc(shift ? 'I' : 'i'); buffstr[i++] = shift ? 'I' : 'i'; break;
                case 24: printc(shift ? 'O' : 'o'); buffstr[i++] = shift ? 'O' : 'o'; break;
                case 25: printc(shift ? 'P' : 'p'); buffstr[i++] = shift ? 'P' : 'p'; break;
                case 30: printc(shift ? 'A' : 'a'); buffstr[i++] = shift ? 'A' : 'a'; break;
                case 31: printc(shift ? 'S' : 's'); buffstr[i++] = shift ? 'S' : 's'; break;
                case 32: printc(shift ? 'D' : 'd'); buffstr[i++] = shift ? 'D' : 'd'; break;
                case 33: printc(shift ? 'F' : 'f'); buffstr[i++] = shift ? 'F' : 'f'; break;
                case 34: printc(shift ? 'G' : 'g'); buffstr[i++] = shift ? 'G' : 'g'; break;
                case 35: printc(shift ? 'H' : 'h'); buffstr[i++] = shift ? 'H' : 'h'; break;
                case 36: printc(shift ? 'J' : 'j'); buffstr[i++] = shift ? 'J' : 'j'; break;
                case 37: printc(shift ? 'K' : 'k'); buffstr[i++] = shift ? 'K' : 'k'; break;
                case 38: printc(shift ? 'L' : 'l'); buffstr[i++] = shift ? 'L' : 'l'; break;
                case 44: printc(shift ? 'Z' : 'z'); buffstr[i++] = shift ? 'Z' : 'z'; break;
                case 45: printc(shift ? 'X' : 'x'); buffstr[i++] = shift ? 'X' : 'x'; break;
                case 46: printc(shift ? 'C' : 'c'); buffstr[i++] = shift ? 'C' : 'c'; break;
                case 47: printc(shift ? 'V' : 'v'); buffstr[i++] = shift ? 'V' : 'v'; break;
                case 48: printc(shift ? 'B' : 'b'); buffstr[i++] = shift ? 'B' : 'b'; break;
                case 49: printc(shift ? 'N' : 'n'); buffstr[i++] = shift ? 'N' : 'n'; break;
                case 50: printc(shift ? 'M' : 'm'); buffstr[i++] = shift ? 'M' : 'm'; break;
                case 57: printc(' '); buffstr[i++] = ' '; break;
                case 53: printc('/'); buffstr[i++] = '/'; break;
                case 28: reading = 0; break;
            }
        }
    }
    buffstr[i] = 0;
    return buffstr;
}