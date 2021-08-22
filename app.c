#include <stdio.h>
#include <string.h>
#include "app.h"
#include "mode.h"
#include "modes/timeset.h"
#include "modes/gregorian.h"
#include "modes/neralie.h"
#include "watch.h"
#include "hal_ext_irq.h"

Application app;

void app_init() {
    memset(&app, 0, sizeof(app));

    // Number of 1Hz ticks until we enter idle
    app.ticks_to_idle = 5;

    timeset_init_mode(&app.modes[MODE_TIME_SET]);
    gregorian_init_mode(&app.modes[MODE_GREGORIAN]);
    neralie_init_mode(&app.modes[MODE_NERALIE]);

    app.current_mode = &app.modes[MODE_TIME_SET];
}

void app_wake_from_deep_sleep() {
    // No deep sleep for us until we get more hardware to wake from it.
}

void app_setup() {
    watch_enable_led(false); // enable LED with plain digital IO, not PWM
    _app_setup_buttons();
    watch_enable_display();

    // Don't forget to init the current mode
    app.current_mode->init();
}

void _app_setup_buttons() {
    watch_enable_buttons();
    watch_register_button_callback(BTN_LIGHT, app_cb_light);
    watch_register_button_callback(BTN_MODE, app_cb_mode);
    watch_register_button_callback(BTN_ALARM, app_cb_alarm);
}

void app_prepare_for_sleep() {
    app.debouncing = false;
}

void app_wake_from_sleep() {}

void app_switch_mode(ApplicationMode mode) {
    if (!app.setup_idle) {
        // Don't idle while we're setting the time at first, do it later.
        app.setup_idle = true;
        watch_register_tick_callback(app_cb_tick);
    }

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

void app_cb_light() {
    if (app.debouncing) return;
    app.debouncing = true;
    app.idle_ticks = 0;

    app.current_mode->cb_light();
}

void app_cb_mode() {
    if (app.debouncing) return;
    app.debouncing = true;
    app.idle_ticks = 0;

    app.current_mode->cb_mode();
}

void app_cb_alarm() {
    if (app.debouncing) return;
    app.debouncing = true;
    app.idle_ticks = 0;

    if (app.idleing) {
        app.idleing = false;

        // Turn the EIC back on, it should still be configured?
        //ext_irq_init();
        _app_setup_buttons();

        // Flash green to indicate we're active again.
        watch_set_led_green();
        delay_ms(250);
        watch_set_led_off();

        return;
    }

    app.current_mode->cb_alarm();
}

void app_cb_tick() {
    app.current_mode->cb_tick();

    if (app.idleing) return;
    
    app.idle_ticks++;
    if (app.ticks_to_idle <= app.idle_ticks) {
        app.idleing = true;
        app.idle_ticks = 0;

        ext_irq_deinit();

        //Flash the green LED to indicate entering idle
        watch_set_led_green();
        delay_ms(250);
        watch_set_led_off();
    }
}