#pragma once
#include "sokol_app.h"


void gui_init();
void gui_show_window();
void gui_input(const sapp_event* event);
void gui_shutdown();