#include "../timer.h"
#include "../vga.h"
#include "uptime.h"
#include "../stdint.h"

unsigned long long int uptime(){
    unsigned long long int uptimeInSeconds = 0;

    uint32_t ticks = getTicks();
    uint32_t freq = getFreq();

    uptimeInSeconds = ticks / freq;

    return uptimeInSeconds;

}
