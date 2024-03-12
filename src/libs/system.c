#include "system.h"

extern uint8 inportb(uint16 _port);
extern void outportb(uint16 _port, uint8 _data);

uint8 callinportb(uint16 _port)
{
    uint8 rv;
    rv = inportb(_port);
    return rv;
}

void calloutportb(uint16 _port, uint8 _data)
{
    outportb(_port, _data);
}