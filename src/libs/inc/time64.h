#ifndef TIME_H
 #define TIME_H
 
 #include <stddef.h>
 
 typedef struct {
     int hour;
     int minute;
     int second;
     int year;
     int month;
     int day;
     int timezone_offset;
 } DateTime;
 
 void setTimezone(const char* timezoneName);
 DateTime get_datetime();
 
 #endif