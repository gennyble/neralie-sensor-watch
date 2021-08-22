#ifndef NERALIE_gregorian_H
#define NERALIE_gregorian_H

#include "mode.h"

void gregorian_init_mode(Mode*);
void gregorian_init();
void gregorian_loop();

void _gregorian_display();

void gregorian_cb_light();
void gregorian_cb_mode();
void gregorian_cb_alarm();
void gregorian_cb_tick();

#endif//NERALIE_gregorian_H