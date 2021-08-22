#ifndef NERALIE_TIMESET_H
#define NERALIE_TIMESET_H

#include <stdint.h>
#include "mode.h"

typedef enum ModeTimeSetPosition {
	HOURS = 0,
	MINUTES,
	SECONDS
} ModeTimeSetPosition;

typedef struct ModeTimeSet {
	ModeTimeSetPosition position;

	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
} ModeTimeSet;

void timeset_init_mode(Mode*);
void timeset_init();
void timeset_loop();

void timeset_cb_light();
void timeset_cb_mode();
void timeset_cb_alarm();

void _timeset_settime();

#endif//NERALIE_TIMESET_H