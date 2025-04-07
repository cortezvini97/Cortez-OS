#ifndef KERNEL_H
 #define KERNEL_H
 
 #include "keyboard64.h"
 #include "stdio64.h"
 #include "shell64.h"
 #include "time64.h"
 
 
 void handle_user_input();
 void kernelShutdownApi();
 void kernelRebootApi();
 void kernelGetDateApi();
 
 #endif