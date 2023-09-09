#include "time.h"

enum {
    TIMELO  = TIME_BASE + 0x04,
    TIMEHI  = TIME_BASE + 0x08,
};

unsigned int timelo() {
    return *(volatile unsigned int *)TIMELO;
}

unsigned int timehi() {
    return *(volatile unsigned int *)TIMEHI;
}

// ====== RAND =======

unsigned int xorshift32(unsigned int state[static 1]) {
    /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
    unsigned int x = state[0];
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state[0] = x;
    return x;
}

unsigned int state[1];  // This needs to be preserved between calls.

void init_rand() {
    state[0] = timelo();
}

unsigned int rand() {
    return xorshift32(state);
}
