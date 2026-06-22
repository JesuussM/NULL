#pragma once
#include "cglm/cglm.h"

void camera_init();
void camera_frame();
void camera_input(const sapp_event* event);
mat4* camera_get_view();