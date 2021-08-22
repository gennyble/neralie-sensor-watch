#ifndef NERALIE_NERALIE_H
#define NERALIE_NERALIE_H

#include "mode.h"

void neralie_init_mode(Mode*);
void neralie_init();
void neralie_loop();

void _neralie_display();

void neralie_cb_light();
void neralie_cb_mode();
void neralie_cb_alarm();
void neralie_cb_tick();

#endif//NERALIE_NERALIE_H