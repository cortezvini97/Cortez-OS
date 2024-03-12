#ifndef SYSTEM_H
#define SYSTEM_H
#include "types.h"

uint8 callinportb (uint16 _port);
void calloutportb (uint16 _port, uint8 _data);

#endif
