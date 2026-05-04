#include "../stdint.h"
#include "zentype.h"
#include "../stdlib/stdio.h"
#include "../vga.h"

#define ZEN_MAX 512
static char zenBuf[ZEN_MAX];
static int  zenLen   = 0;
static int  zenWords = 0;
static int  zenChars = 0;

static void zenCountStats(void) {
    zenWords = 0; zenChars = 0;
    int inWord = 0;
    for (int i = 0; i < zenLen; i++) {
        char c = zenBuf[i];
        if (c != ' ' && c != '\n' && c != '\t') {
            zenChars++;
            if (!inWord) { zenWords++; inWord = 1; }
        } else {
            inWord = 0;
        }
    }
}

void zentypeInit(void) {
    zenLen = 0; zenWords = 0; zenChars = 0;
    Reset();
    print("  ZEN TYPING\n");
    print("  ----------\n");
    print("  Clear your mind. Just type.\n");
    print("  ESC to return to menu.\n\n");
    print("  Words: 0   Chars: 0\n\n");
}

int zentypeHandleKey(char c) {
    if (c == 27) return 1;
    if (c == '\b') {
        if (zenLen > 0) {
            zenLen--;
            zenBuf[zenLen] = 0;
            printf("\b");
            zenCountStats();
        }
        return 0;
    }
    if ((c >= 32 && c < 127) || c == '\n') {
        if (zenLen < ZEN_MAX - 1) {
            zenBuf[zenLen++] = c;
            zenBuf[zenLen]   = 0;
            printf("%c", c);
            zenCountStats();
        }
    }
    return 0;
}
