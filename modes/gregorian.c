#include <stdio.h>
#include <string.h>
#include "app.h"
#include "mode.h"
#include "modes/gregorian.h"
#include "watch.h"

static ModeGregorian data;

void gregorian_init_mode(Mode *mode) {
	memset(&data, 0, sizeof(data));

	mode->init = gregorian_init;
	mode->loop = gregorian_loop;
	mode->cb_tick = gregorian_cb_tick;
	mode->cb_light = gregorian_cb_light;
	mode->cb_mode = gregorian_cb_mode;
	mode->cb_alarm = gregorian_cb_alarm;
}

void gregorian_init() {
	// Clear the display by setting the ten indicators to zero
	watch_display_string("          ", 0);
	watch_clear_all_indicators();

	watch_set_colon();
	if (data.display_in_24h) {
		watch_set_indicator(WATCH_INDICATOR_24H);
	}

	// Update right away to avoid a blank display
	_gregorian_display();
}

void gregorian_loop() {
	_gregorian_display();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-overflow"
void _gregorian_display() {
	char buf[7] = {0};

	struct calendar_date_time date_time;
	watch_get_date_time(&date_time);

	if (!data.display_in_24h) {
		if (date_time.time.hour >= 12) {
			watch_set_indicator(WATCH_INDICATOR_PM);

			if (date_time.time.hour >= 13)
				date_time.time.hour -= 12;
		}
	}

	sprintf(buf, "%2d%02d%02d", date_time.time.hour, date_time.time.min, date_time.time.sec);
	watch_display_string(buf, 4);
}
#pragma GCC diagnostic pop

void _gregorian_switch_time_mode() {
	if (data.display_in_24h) {
		data.display_in_24h = false;
		watch_clear_indicator(WATCH_INDICATOR_24H);
	} else {
		data.display_in_24h = true;
		watch_clear_indicator(WATCH_INDICATOR_PM);
		watch_set_indicator(WATCH_INDICATOR_24H);
	}

	_gregorian_display();
}

void gregorian_cb_light() {
	app_light_led(3);
}

void gregorian_cb_mode() {
	app_switch_mode(MODE_NERALIE);
}

void gregorian_cb_alarm() {
	_gregorian_switch_time_mode();
}

void gregorian_cb_tick() {
	if (app.led_powered && app.lit_led_ticks == 1 && watch_get_pin_level(BTN_LIGHT)) {
		app.lit_led_ticks++;
		app_reset_idle_timer();
	}
}