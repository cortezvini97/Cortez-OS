#include "time.h"
#include "system.h"
#include "string.h"
#include "stdio.h"

typedef struct {
    const char* name;
    int offset; // Offset em minutos
} TimezoneEntry;

static TimezoneEntry timezones[] = {
    {"UTC", 0},
    {"America/Sao_Paulo", -180},
    {"America/Brasilia", -180}, // Sinônimo de São Paulo
    {"America/New_York", -300},
    {"America/Los_Angeles", -480},
    {"America/Chicago", -360},
    {"America/Denver", -420},
    {"America/Mexico_City", -360},
    {"America/Buenos_Aires", -180},
    {"America/Lima", -300},
    {"America/Bogota", -300},
    {"Europe/London", 0},
    {"Europe/Berlin", 60},
    {"Europe/Paris", 60},
    {"Europe/Madrid", 60},
    {"Europe/Rome", 60},
    {"Europe/Moscow", 180},
    {"Europe/Istanbul", 180},
    {"Asia/Tokyo", 540},
    {"Asia/Shanghai", 480},
    {"Asia/Hong_Kong", 480},
    {"Asia/Singapore", 480},
    {"Asia/Dubai", 240},
    {"Asia/Kolkata", 330},
    {"Asia/Jakarta", 420},
    {"Australia/Sydney", 600},
    {"Australia/Melbourne", 600},
    {"Australia/Brisbane", 600},
    {"Australia/Perth", 480},
    {"Pacific/Auckland", 720},
    {"Africa/Johannesburg", 120},
    {"Africa/Cairo", 120},
    {"Africa/Lagos", 60},
    {"Antarctica/Palmer", -180},
    {"Indian/Maldives", 300},
    {NULL, 0} // Terminador da lista
};

void setTimezone(const char* timezoneName) {
    for (int i = 0; timezones[i].name != NULL; i++) {
        if (strEql(timezoneName, timezones[i].name)) {
            set_timezone(timezones[i].offset);
            printf("\nFuso atualizado para %s (UTC %+d:%02d)\n", 
                   timezones[i].name, timezones[i].offset / 60, timezones[i].offset % 60);
            return;
        }
    }
    printf("\nErro: Fuso '%s' não encontrado.\n", timezoneName);
}

DateTime get_datetime() {
    uint8 seconds = read_rtc_register(0x00);
    uint8 minutes = read_rtc_register(0x02);
    uint8 hours   = read_rtc_register(0x04);
    uint8 day     = read_rtc_register(0x07);
    uint8 month   = read_rtc_register(0x08);
    uint8 year    = read_rtc_register(0x09);

    seconds = (seconds & 0x0F) + ((seconds >> 4) * 10);
    minutes = (minutes & 0x0F) + ((minutes >> 4) * 10);
    hours   = (hours & 0x0F) + ((hours >> 4) * 10);
    day     = (day & 0x0F) + ((day >> 4) * 10);
    month   = (month & 0x0F) + ((month >> 4) * 10);
    year    = (year & 0x0F) + ((year >> 4) * 10);

    DateTime dateTime;
    dateTime.hour = hours;
    dateTime.minute = minutes;
    dateTime.second = seconds;
    dateTime.day = day;
    dateTime.month = month;
    dateTime.year = year;
    dateTime.timezone_offset = get_systimezone();

    int total_minutes = (hours * 60) + minutes + get_systimezone();
    dateTime.day += total_minutes / 1440;
    total_minutes %= 1440;
    
    if (total_minutes < 0) {
        total_minutes += 1440;
        dateTime.day--;
    }
    
    dateTime.hour = (total_minutes / 60) % 24;
    dateTime.minute = total_minutes % 60;

    if (dateTime.day <= 0) {
        dateTime.month--;
        if (dateTime.month <= 0) {
            dateTime.month = 12;
            dateTime.year--;
        }
        dateTime.day = get_days_in_month(dateTime.month, dateTime.year);
    } else if (dateTime.day > get_days_in_month(dateTime.month, dateTime.year)) {
        dateTime.day = 1;
        dateTime.month++;
        if (dateTime.month > 12) {
            dateTime.month = 1;
            dateTime.year++;
        }
    }

    return dateTime;
}

int get_days_in_month(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
        default:
            return 0;
    }
}