#include "../stdint.h"
#include "stopwatch.h"
#include "../stdlib/stdio.h"
#include "../vga.h"
#include "../timer.h"

static int      swRunning   = 0;
static int      swLaps      = 0;
static uint32_t swStartTick = 0;
static uint32_t swElapsed   = 0;

#define MAX_LAPS 10
static uint32_t swLapTimes[MAX_LAPS];

extern uint64_t ticks;

static void swPrintTime(uint32_t t) {
    uint32_t centis  = t % 100;
    uint32_t seconds = (t / 100) % 60;
    uint32_t minutes = (t / 6000) % 60;
    uint32_t hours   = t / 360000;
    if (hours > 0) printf("%d:", hours);
    if (minutes < 10) printf("0");
    printf("%d:", minutes);
    if (seconds < 10) printf("0");
    printf("%d.", seconds);
    if (centis < 10) printf("0");
    printf("%d", centis);
}

static void swRedraw(void) {
    Reset();
    print("  STOPWATCH\n");
    print("  ---------\n\n");
    print("  Time:  ");
    uint32_t now     = (uint32_t)ticks;
    uint32_t display = swElapsed;
    if (swRunning) display = swElapsed + (now - swStartTick);
    swPrintTime(display);
    print("\n\n");
    if (!swRunning)
        print("  [S] Start  ");
    else
        print("  [S] Stop   ");
    print("[R] Reset  [L] Lap  [ESC] Menu\n\n");
    if (swLaps > 0) {
        print("  Laps:\n");
        for (int i = 0; i < swLaps; i++) {
            printf("    Lap %d:  ", i + 1);
            swPrintTime(swLapTimes[i]);
            print("\n");
        }
    }
}

void stopwatchInit(void) {
    swRunning = 0; swElapsed = 0;
    swStartTick = 0; swLaps = 0;
    swRedraw();
}

void stopwatchOnTick(void) {
    if (swRunning) swRedraw();
}

int stopwatchHandleKey(char c) {
    if (c == 27) return 1;
    switch (c) {
        case 's': case 'S':
            if (!swRunning) {
                swStartTick = (uint32_t)ticks;
                swRunning = 1;
            } else {
                swElapsed += (uint32_t)ticks - swStartTick;
                swRunning = 0;
            }
            swRedraw(); break;
        case 'r': case 'R':
            swRunning = 0; swElapsed = 0;
            swStartTick = 0; swLaps = 0;
            swRedraw(); break;
        case 'l': case 'L':
            if (swRunning && swLaps < MAX_LAPS) {
                uint32_t now = (uint32_t)ticks;
                swLapTimes[swLaps++] = swElapsed + (now - swStartTick);
                swRedraw();
            }
            break;
    }
    return 0;
}
