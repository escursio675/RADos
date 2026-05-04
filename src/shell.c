#include "shell.h"
#include "vga.h"
#include "stdlib/stdio.h"
#include "shutdown.h"
#include "apps/calculator.h"
#include "apps/stopwatch.h"
#include "apps/zentype.h"
#include "util.h"

typedef enum {
    APP_NONE = 0,
    APP_CALCULATOR,
    APP_STOPWATCH,
    APP_ZEN
} ActiveApp;

static char      shellBuf[SHELL_BUF_SIZE];
static int       shellLen = 0;
static ActiveApp activeApp = APP_NONE;

static int strEq(const char* a, const char* b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++; b++;
    }
    return *a == 0 && *b == 0;
}

static void shellClearBuf(void) {
    for (int i = 0; i < SHELL_BUF_SIZE; i++) shellBuf[i] = 0;
    shellLen = 0;
}

static void printMenu(void) {
    Reset();
    print("================================\n");
    print("           RADos v1.0\n");
    print("================================\n\n");
    print("  calc      - Calculator\n");
    print("  stopwatch - Stopwatch\n");
    print("  zen       - Zen typing\n\n");
    print("  help      - Show this menu\n");
    print("  clear     - Clear screen\n");
    print("  shutdown  - Power off\n\n");
    print("--------------------------------\n");
    print("  > ");
}

static void shellPrompt(void) {
    print("\n  > ");
}

static void shellDispatch(const char* cmd) {
    if (strEq(cmd, "calc")) {
        activeApp = APP_CALCULATOR;
        calcInit();
    } else if (strEq(cmd, "stopwatch") || strEq(cmd, "sw")) {
        activeApp = APP_STOPWATCH;
        stopwatchInit();
    } else if (strEq(cmd, "zen")) {
        activeApp = APP_ZEN;
        zentypeInit();
    } else if (strEq(cmd, "help") || strEq(cmd, "clear")) {
        printMenu();
    } else if (strEq(cmd, "shutdown") || strEq(cmd, "exit") || strEq(cmd, "quit")) {
        shutdownMachine();
    } else if (cmd[0] == 0) {
        shellPrompt();
    } else {
        print("\n  Unknown command: ");
        print(cmd);
        print("\n  Type 'help' for commands\n");
        shellPrompt();
    }
}

void shellInit(void) {
    shellClearBuf();
    activeApp = APP_NONE;
    printMenu();
}

void shellHandleKey(char c) {
    if (activeApp == APP_CALCULATOR) {
        if (calcHandleKey(c)) {
            activeApp = APP_NONE;
            printMenu();
        }
        return;
    }
    if (activeApp == APP_STOPWATCH) {
        if (stopwatchHandleKey(c)) {
            activeApp = APP_NONE;
            printMenu();
        }
        return;
    }
    if (activeApp == APP_ZEN) {
        if (zentypeHandleKey(c)) {
            activeApp = APP_NONE;
            printMenu();
        }
        return;
    }

    if (c == '\n') {
        shellBuf[shellLen] = 0;
        shellDispatch(shellBuf);
        shellClearBuf();
    } else if (c == '\b') {
        if (shellLen > 0) {
            shellLen--;
            shellBuf[shellLen] = 0;
            printf("\b");
        }
    } else if (shellLen < SHELL_BUF_SIZE - 1) {
        shellBuf[shellLen++] = c;
        printf("%c", c);
    }
}
