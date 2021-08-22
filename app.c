#include <stdio.h>
#include <string.h>
#include "app.h"
#include "mode.h"
#include "modes/timeset.h"
#include "modes/clock.h"
#include "watch.h"

Application app;

void cb_light_pressed();
void cb_mode_pressed();
void cb_alarm_pressed();

void app_init() {
    timeset_init_mode(&app.modes[MODE_TIME_SET]);
    clock_init_mode(&app.modes[MODE_CLOCK]);

    app.current_mode = &app.modes[MODE_TIME_SET];
}

void app_wake_from_deep_sleep() {
    // No deep sleep for us until we get more hardware to wake from it.
}

void app_setup() {
    watch_enable_led(false); // enable LED with plain digital IO, not PWM

    watch_enable_buttons();
    watch_register_button_callback(BTN_LIGHT, cb_light_pressed);
    watch_register_button_callback(BTN_MODE, cb_mode_pressed);
    watch_register_button_callback(BTN_ALARM, cb_alarm_pressed);

    watch_enable_display();

    // Don't forget to init the current mode
    app.current_mode->init();
}

void app_prepare_for_sleep() {
    app.debouncing = false;
}

void app_wake_from_sleep() {}

void app_switch_mode(ApplicationMode mode) {
    if (&app.modes[mode] != app.current_mode) {
        app.modes[mode].init();
        app.current_mode = &app.modes[mode];
    }
}

bool app_loop() {
    app.current_mode->loop();

    // Wait a moment to debounce button input
    delay_ms(250);

    return true;
}

void cb_light_pressed() {
    if (app.debouncing) return;
    app.debouncing = true;

    app.current_mode->cb_light();
}

void cb_mode_pressed() {
    if (app.debouncing) return;
    app.debouncing = true;

    app.current_mode->cb_mode();
}

void cb_alarm_pressed() {
    if (app.debouncing) return;
    app.debouncing = true;

    app.current_mode->cb_alarm();
}
