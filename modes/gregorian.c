#include <stdio.h>
#include "mode.h"
#include "modes/clock.h"
#include "watch.h"

void clock_init_mode(Mode *mode) {
	mode->init = clock_init;
	mode->loop = clock_loop;
	mode->cb_light = clock_cb_light;
	mode->cb_mode = clock_cb_mode;
	mode->cb_alarm = clock_cb_alarm;
}

void clock_init() {
	// Clear the display by setting the ten indicators to zero
	watch_display_string("          ", 0);

	watch_set_indicator(WATCH_INDICATOR_24H);
	watch_register_tick_callback(clock_cb_tick);
}

void clock_loop() {
	_clock_display();
}

void _clock_display() {
	char buf[7] = {0};

	struct calendar_date_time date_time;
	watch_get_date_time(&date_time);
	sprintf(buf, "%2d%02d%02d", date_time.time.hour, date_time.time.min, date_time.time.sec);
	watch_display_string(buf, 4);
	watch_set_colon();
}

void clock_cb_light() {}
void clock_cb_mode() {}
void clock_cb_alarm() {}

void clock_cb_tick() {}