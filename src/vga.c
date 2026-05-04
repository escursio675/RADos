#include "vga.h"
#include "stdint.h"

uint16_t column = 0;
uint16_t line   = 0;

uint16_t* const vga = (uint16_t* const) 0xC00B8000;

uint16_t currentColor = 0x0700;  // light grey on black, hardcoded so it works at boot
const uint16_t defaultColor = 0x0700;

void vgaInit(void) {
    column       = 0;
    line         = 0;
    currentColor = 0x0700;
    for (uint16_t y = 0; y < VGA_HEIGHT; y++) {
        for (uint16_t x = 0; x < VGA_WIDTH; x++) {
            vga[y * VGA_WIDTH + x] = 0x0700 | (uint16_t)' ';
        }
    }
}

void Reset(void) {
    column       = 0;
    line         = 0;
    currentColor = defaultColor;
    for (uint16_t y = 0; y < VGA_HEIGHT; y++) {
        for (uint16_t x = 0; x < VGA_WIDTH; x++) {
            vga[y * VGA_WIDTH + x] = (uint16_t)' ' | defaultColor;
        }
    }
}

void newLine(void) {
    if (line < VGA_HEIGHT - 1) {
        line++;
        column = 0;
    } else {
        scrollUp();
        column = 0;
    }
}

void scrollUp(void) {
    for (uint16_t y = 1; y < VGA_HEIGHT; y++) {
        for (uint16_t x = 0; x < VGA_WIDTH; x++) {
            vga[(y - 1) * VGA_WIDTH + x] = vga[y * VGA_WIDTH + x];
        }
    }
    for (uint16_t x = 0; x < VGA_WIDTH; x++) {
        vga[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = (uint16_t)' ' | currentColor;
    }
}

void print(const char* s) {
    while (*s) {
        switch (*s) {
            case '\n':
                newLine();
                break;
            case '\r':
                column = 0;
                break;
            case '\b':
                if (column == 0 && line != 0) {
                    line--;
                    column = VGA_WIDTH;
                }
                if (column > 0) {
                    column--;
                }
                vga[line * VGA_WIDTH + column] = (uint16_t)' ' | currentColor;
                break;
            case '\t': {
                if (column == VGA_WIDTH) {
                    newLine();
                }
                uint16_t tabLen = 4 - (column % 4);
                while (tabLen != 0) {
                    vga[line * VGA_WIDTH + column] = (uint16_t)' ' | currentColor;
                    column++;
                    tabLen--;
                }
                break;
            }
            default:
                if (column == VGA_WIDTH) {
                    newLine();
                }
                vga[line * VGA_WIDTH + column] = ((uint16_t)(unsigned char)*s) | currentColor;
                column++;
                break;
        }
        s++;
    }
}