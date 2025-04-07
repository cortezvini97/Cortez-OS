#ifndef KERNEL_H
#define KERNEL_H

#include "keyboard.h"
#include "stdio.h"
#include "shell.h"
#include "time.h"


void handle_user_input();
void kernelShutdownApi();
void kernelRebootApi();
void kernelGetDateApi();

#endif