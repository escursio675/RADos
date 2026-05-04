#ifndef VGA_H
#define VGA_H

#include "stdint.h"

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

typedef enum {
    COLOR8_BLACK         = 0,
    COLOR8_BLUE          = 1,
    COLOR8_GREEN         = 2,
    COLOR8_CYAN          = 3,
    COLOR8_RED           = 4,
    COLOR8_MAGENTA       = 5,
    COLOR8_BROWN         = 6,
    COLOR8_LIGHT_GREY    = 7,
    COLOR8_DARK_GREY     = 8,
    COLOR8_LIGHT_BLUE    = 9,
    COLOR8_LIGHT_GREEN   = 10,
    COLOR8_LIGHT_CYAN    = 11,
    COLOR8_LIGHT_RED     = 12,
    COLOR8_LIGHT_MAGENTA = 13,
    COLOR8_YELLOW        = 14,
    COLOR8_WHITE         = 15
} vga_color;

extern uint16_t        column;
extern uint16_t        line;
extern uint16_t        currentColor;
extern const uint16_t  defaultColor;
extern uint16_t* const vga;

void vgaInit(void);
void Reset(void);
void newLine(void);
void scrollUp(void);
void print(const char* s);

#endif