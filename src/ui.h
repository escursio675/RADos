#ifndef UI_H
#define UI_H

#include "stdint.h"
#include "vga.h"

#define UI_COLOR_TITLE   0x0B
#define UI_COLOR_NORMAL  0x07
#define UI_COLOR_SUCCESS 0x0A
#define UI_COLOR_ERROR   0x0C
#define UI_COLOR_DIM     0x08
#define UI_COLOR_ACCENT  0x0E
#define UI_COLOR_INPUT   0x0F

void uiClear(void);
void uiSetColor(uint8_t fg, uint8_t bg);
void uiResetColor(void);
void uiDrawHLine(char c, int len);
void uiPrintCentered(const char* s, int w);
void uiPrintAt(int col, int row, const char* s);
void uiDrawBox(int x, int y, int w, int h);
void uiPrintMainMenu(void);

#endif