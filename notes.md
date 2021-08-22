# Notes

## Saving Power by Disabling The Interrupt Handler
The EIC apparently uses ~5µA and is used for the light and mode buttons, but not the alarm. It's activated by `watch_enable_buttons()`, but there is no disable. It would be great if we could disable them when we want. It'd let you enter a sort of idle where the watch still runs, but light and mode are disabled. You'd have to press Alarm to "wake" the watch, which could maybe be indicated by flashing one of the LEDs. You can then use light/mode.

## Weird `7` In The Tens Minutes Digit
It was displayed as the middle segment and the bottom leftmost one, why? We have all the segments there to display it, they're used in other numbers.