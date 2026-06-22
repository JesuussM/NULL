#include "sokol_time.h"

extern uint64_t start_time;
extern uint64_t last_time;
extern float delta_time;
extern bool DEBUG_MODE;

void DEBUG_TOGGLE(const sapp_event* event);
