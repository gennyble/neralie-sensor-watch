#ifndef MODE_H
#define MODE_H

typedef struct Mode {
	void (*init)();
	void (*loop)();
	void (*cb_tick)();
	void (*cb_light)();
	void (*cb_mode)();
	void (*cb_alarm)();
} Mode;

#endif//MODE_H