#ifndef _SETUP_H
#define _SETUP_H

void setup();
void set_delay();

#define ADDRESS 0x48
#define BASE 64
#define A0 BASE
#define FACTOR_DELAY 10

extern const int pinouts[];

#endif
