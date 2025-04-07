#ifndef SHELL_CODE_H
#define SHELL_CODE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char* getShellCode();
char* shellcode_to_string(unsigned char* shellcode, size_t len);

#endif