#include "ui.h"
#include "vga.h"
#include "stdlib/stdio.h"

void uiSetColor(uint8_t fg, uint8_t bg) {
    currentColor = ((uint16_t)bg << 12) | ((uint16_t)fg << 8);
}

void uiResetColor(void) {
    currentColor = defaultColor;
}

void uiClear(void) {
    uiResetColor();
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga[y * VGA_WIDTH + x] = (uint16_t)' ' | currentColor;
        }
    }
    column = 0;
    line   = 0;
}

void uiDrawHLine(char c, int len) {
    for (int i = 0; i < len; i++) {
        printf("%c", c);
    }
}

void uiPrintCentered(const char* s, int w) {
    int len = 0;
    const char* p = s;
    while (*p++) len++;
    int pad = (w - len) / 2;
    for (int i = 0; i < pad; i++) printf(" ");
    printf("%s", s);
}

void uiPrintAt(int col, int row, const char* s) {
    column = (uint16_t)col;
    line   = (uint16_t)row;
    printf("%s", s);
}

void uiDrawBox(int x, int y, int w, int h) {
    uiPrintAt(x, y, "+");
    column = (uint16_t)(x + 1);
    for (int i = 0; i < w - 2; i++) printf("-");
    printf("+");
    for (int i = 1; i < h - 1; i++) {
        uiPrintAt(x,         y + i, "|");
        uiPrintAt(x + w - 1, y + i, "|");
    }
    uiPrintAt(x, y + h - 1, "+");
    column = (uint16_t)(x + 1);
    for (int i = 0; i < w - 2; i++) printf("-");
    printf("+");
}

void uiPrintMainMenu(void) {
    uiClear();

    uiSetColor(UI_COLOR_ACCENT, 0);
    uiDrawHLine('=', 80);
    printf("\n");

    uiSetColor(UI_COLOR_TITLE, 0);
    uiPrintCentered("*** RADos ***", 80);
    printf("\n");

    uiSetColor(UI_COLOR_DIM, 0);
    uiPrintCentered("A tiny x86 kernel", 80);
    printf("\n");

    uiSetColor(UI_COLOR_ACCENT, 0);
    uiDrawHLine('=', 80);
    printf("\n\n");

    uiSetColor(UI_COLOR_NORMAL, 0);
    printf("  Programs:\n\n");

    uiSetColor(UI_COLOR_SUCCESS, 0);
    printf("    calc        ");
    uiSetColor(UI_COLOR_NORMAL, 0);
    printf("- Calculator (+ - * /)\n");

    uiSetColor(UI_COLOR_SUCCESS, 0);
    printf("    stopwatch   ");
    uiSetColor(UI_COLOR_NORMAL, 0);
    printf("- Stopwatch (start, stop, reset, lap)\n");

    uiSetColor(UI_COLOR_SUCCESS, 0);
    printf("    zen         ");
    uiSetColor(UI_COLOR_NORMAL, 0);
    printf("- Zen typing mode\n\n");

    uiSetColor(UI_COLOR_NORMAL, 0);
    printf("  System:\n\n");

    uiSetColor(UI_COLOR_ACCENT, 0);
    printf("    help        ");
    uiSetColor(UI_COLOR_NORMAL, 0);
    printf("- Show this help\n");

    uiSetColor(UI_COLOR_ACCENT, 0);
    printf("    clear       ");
    uiSetColor(UI_COLOR_NORMAL, 0);
    printf("- Clear screen\n");

    uiSetColor(UI_COLOR_ERROR, 0);
    printf("    shutdown    ");
    uiSetColor(UI_COLOR_NORMAL, 0);
    printf("- Power off the machine\n\n");

    uiSetColor(UI_COLOR_DIM, 0);
    uiDrawHLine('-', 80);
    printf("\n");

    uiSetColor(UI_COLOR_INPUT, 0);
    printf("  > ");
    uiResetColor();
}