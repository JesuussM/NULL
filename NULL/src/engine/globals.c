#include "sokol_app.h"

#include <stdbool.h>

#include "globals.h"

uint64_t start_time = 0;
uint64_t last_time = 0;
float delta_time = 0;
bool DEBUG_MODE = false;

void DEBUG_TOGGLE(const sapp_event* event) {
	if (event->type == SAPP_EVENTTYPE_KEY_DOWN) {
		if (event->key_repeat) return;
		if (event->key_code == SAPP_KEYCODE_F1) { 
			if (DEBUG_MODE) {
				DEBUG_MODE = false;
			}
			else {
				DEBUG_MODE = true;
			}
		}
	}
	
	if (DEBUG_MODE) {
		sapp_lock_mouse(false);
	}
	else {
		sapp_lock_mouse(true);
	}

}