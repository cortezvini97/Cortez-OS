#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"
#include "video64.h"

uint8 inportb (uint16 _port);
void outportb (uint16 _port, uint8 _data);
int32 write(int fd, const char *buf, uint32 count);
uint8 read_rtc_register(uint8 reg);
void set_timezone(int timezone);
int get_systimezone();
void sleep(unsigned int delay);
void shutdown();
void reboot();

#endif