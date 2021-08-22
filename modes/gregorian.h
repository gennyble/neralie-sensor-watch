#ifndef NERALIE_CLOCK_H
#define NERALIE_CLOCK_H

#include "mode.h"

void clock_init_mode(Mode*);
void clock_init();
void clock_loop();

void clock_cb_light();
void clock_cb_mode();
void clock_cb_alarm();
void clock_cb_tick();

#endif//NERALIE_CLOCK_H