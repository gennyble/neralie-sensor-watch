#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include "mode.h"

typedef enum ApplicationMode {
    MODE_TIME_SET = 0, // Initial mode to force time set
    MODE_CLOCK,        // Displays month, day, time.
    NUM_MODES          // Idea taken from Joey's BME280 project
} ApplicationMode;

typedef struct Application {
    Mode modes[NUM_MODES];
    Mode *current_mode;

    bool debouncing;
} Application;

extern Application app;

void app_switch_mode(ApplicationMode);

#endif//APP_H