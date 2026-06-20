#pragma once
#include "sokol_gfx.h"

void renderer_init();
void renderer_draw();

sg_pass_action* renderer_get_pass_action();