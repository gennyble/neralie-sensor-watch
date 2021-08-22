#ifndef APP_H
#define APP_H

#include <stdint.h>
#include <stdbool.h>
#include "mode.h"

typedef enum ApplicationMode {
    MODE_TIME_SET = 0, // Initial mode to force time set
    MODE_GREGORIAN,    // Displays month, day, time.
    MODE_NERALIE,
    NUM_MODES          // Idea taken from Joey's BME280 project
} ApplicationMode;

typedef struct Application {
    Mode modes[NUM_MODES];
    Mode *current_mode;

    bool setup_idle;
    bool idleing;
    uint8_t ticks_to_idle;
    uint8_t idle_ticks;

    bool debouncing;
} Application;

extern Application app;

void _app_setup_buttons();

void app_cb_light();
void app_cb_mode();
void app_cb_alarm();
void app_cb_tick();

void app_switch_mode(ApplicationMode);

#endif//APP_H