#include "system64.h"

extern uint8 system_inportb(uint16 _port);
extern void system_outportb(uint16 _port, uint8 _data);
extern void system_shutdown();
extern void system_reboot();

int sys_timezone = 0;

uint8 inportb(uint16 port){
    return system_inportb(port);
}

void outportb(uint16 port, uint8 data){
    system_outportb(port, data);
}

int32 write(int fd, const char *buf, uint32 count){
    if (fd != 1) {
        return -1;
    }

    uint32 bytes_written = 0;

    for(uint32 i = 0; i < count; i++){
        printc(buf[i]);
        bytes_written++;
    }

    return bytes_written;
}

uint8 read_rtc_register(uint8 reg) {
    outportb(0x70, reg);
    return inportb(0x71);
}

void set_timezone(int timezone){
    sys_timezone = timezone;
}

int get_systimezone(){
    return sys_timezone;
}

void sleep(unsigned int delay) {
    unsigned int i = 0;
    while (1)
    {
        if(i < delay){
            i++;
            continue;
        }
        break;
    }
    
}

void shutdown(){
    system_shutdown();
}

void reboot(){
    system_reboot();
}