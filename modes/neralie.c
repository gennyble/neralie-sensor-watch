#include <stdio.h>
#include "app.h"
#include "mode.h"
#include "modes/neralie.h"
#include "watch.h"

void neralie_init_mode(Mode *mode) {
	mode->init = neralie_init;
	mode->loop = neralie_loop;
	mode->cb_tick = neralie_cb_tick;
	mode->cb_light = neralie_cb_light;
	mode->cb_mode = neralie_cb_mode;
	mode->cb_alarm = neralie_cb_alarm;
}

void neralie_init() {
	// Clear the display by setting the ten indicators to zero
	watch_display_string("          ", 0);
	watch_clear_all_indicators();
	watch_clear_colon();

	// Update right away to avoid an empty display
	_neralie_display();
}

void neralie_loop() {
	_neralie_display();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-overflow"
void _neralie_display() {
	char buf[7] = {0};

	struct calendar_date_time date_time;
	watch_get_date_time(&date_time);

	uint32_t total_ms = ((date_time.time.hour * 60 * 60) + (date_time.time.min * 60) + date_time.time.sec) * 1000;
	uint32_t total_decapulse = total_ms / 864;

	uint16_t beats = total_decapulse / 100;
	uint16_t decapulse = total_decapulse % 100;

	sprintf(buf, "%3d %2d", beats, decapulse);
	watch_display_string(buf, 4);
}
#pragma GCC diagnostic pop

void neralie_cb_light() {}
void neralie_cb_mode() {
	app_switch_mode(MODE_GREGORIAN);
}
void neralie_cb_alarm() {}

void neralie_cb_tick() {}