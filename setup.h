#ifndef _SETUP_H
#define _SETUP_H

void setup();
void set_delay();

#define ADDRESS 0x48
#define BASE 64
#define POTE BASE + 3
#define FACTOR_DELAY 10

extern const int leds_pinout[];

#endif
