#include "stdio64.h"
#include "system64.h"

void int_to_str_padded(int num, char *str, int min_width, char pad_char) {
    int i = 0;
    int isNegative = 0;
    
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num != 0);

    if (isNegative) {
        str[i++] = '-';
    }

    // Preenchimento com caracteres extras se necessário
    while (i < min_width) {
        str[i++] = pad_char;
    }

    str[i] = '\0';

    // Inverter string
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    int index = 0;
    char temp[20];

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i+1] != '\0') {
            i++;

            int min_width = 0;
            char pad_char = ' ';

            // Verifica se há um padding (ex: %02d)
            if (format[i] == '0') {
                pad_char = '0';
                i++; 
            }
            while (format[i] >= '0' && format[i] <= '9') {
                min_width = min_width * 10 + (format[i] - '0');
                i++;
            }

            switch (format[i]) {
                case 'd': { 
                    int num = va_arg(args, int);
                    int_to_str_padded(num, temp, min_width, pad_char);
                    for (int j = 0; temp[j] != '\0'; j++) {
                        buffer[index++] = temp[j];
                    }
                    break;
                }
                case 's': { 
                    char *str = va_arg(args, char*);
                    for (int j = 0; str[j] != '\0'; j++) {
                        buffer[index++] = str[j];
                    }
                    break;
                }
                case 'c': { 
                    char ch = (char)va_arg(args, int);
                    buffer[index++] = ch;
                    break;
                }
                default:
                    buffer[index++] = format[i];
                    break;
            }
        } else {
            buffer[index++] = format[i];
        }
    }

    va_end(args);

    write(1, buffer, index);

    return index;
}