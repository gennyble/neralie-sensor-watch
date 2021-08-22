#include <stddef.h>
#include <string.h>
#include "app.h"
#include "timeset.h"
#include "mode.h"
#include "watch.h"

static ModeTimeSet data;

void timeset_init_mode(Mode *mode) {
	memset(&data, 0, sizeof(data));

	mode->init = timeset_init;
	mode->loop = timeset_loop;
	mode->cb_light = timeset_cb_light;
	mode->cb_mode = timeset_cb_mode;
	mode->cb_alarm = timeset_cb_alarm;
}

void timeset_init() {
	watch_display_string("TS", 0);
}

void timeset_loop() {
	char buf[16] = {0};

	switch (data.position) {
		case HOURS:
			sprintf(buf, "%02d    ", data.hours);
			watch_display_string(buf, 4);
		break;
		case MINUTES:
			sprintf(buf, "  %02d  ", data.minutes);
			watch_display_string(buf, 4);
		break;
		case SECONDS:
			sprintf(buf, "    %02d", data.seconds);
			watch_display_string(buf, 4);
		break;
	}
}

void timeset_cb_light() {
	switch (data.position) {
		case HOURS:
			if (data.hours < 24) {
				data.hours++;
			}
		break;
		case MINUTES:
			if (data.minutes < 59) {
				data.minutes++;
			}
		break;
		case SECONDS:
			if (data.seconds < 59) {
				data.seconds++;
			}
		break;
	}
}

void timeset_cb_mode() {
	switch (data.position) {
		case HOURS:
			if (data.hours > 0) {
				data.hours--;
			}
		break;
		case MINUTES:
			if (data.minutes > 0) {
				data.minutes--;
			}
		break;
		case SECONDS:
			if (data.seconds > 0) {
				data.seconds--;
			}
		break;
	}
}

void timeset_cb_alarm() {
	switch (data.position) {
		case HOURS:
			data.position = MINUTES;
		break;
		case MINUTES:
			data.position = SECONDS;
		break;
		case SECONDS:
			_timeset_settime();
			app_switch_mode(MODE_GREGORIAN);
		break;
	}
}

void _timeset_settime() {
	struct calendar_date_time date_time;
	date_time.time.hour = data.hours;
	date_time.time.min = data.minutes;
	date_time.time.sec = data.seconds;

	watch_set_date_time(date_time);
}