#ifndef VIDEO_H
#define VIDEO_H

#include "system.h"

void setisUpdateCursor(int update);
void setCursorPosition(int cursorXvalue, int cursorYValue);
void clearLine(uint8 from,uint8 to);
void updateCursor();
void clearScreen();
void scrollUp(uint8 lineNumber);
void scrollDown(uint8 lineNumber);
void newLineCheck();
void printc(char c);
void set_screen_color_from_color_code(int color_code);
void set_screen_color(int text_color,int bg_color);
void print_colored(string ch,int text_color,int bg_color);

#endif