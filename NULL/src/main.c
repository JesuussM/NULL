#define SOKOL_IMPL
#define SOKOL_D3D11

#include <stdio.h>
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_log.h"
#include "renderer.h"

void init() 
{
	renderer_init();
}

void frame()
{
	renderer_draw();
}

void cleanup() 
{
	sg_shutdown();
}

void event(const sapp_event* event)
{
	if (event->type == SAPP_EVENTTYPE_KEY_DOWN)
	{
		// If ESC is pressed, quit
		if (event->key_code == SAPP_KEYCODE_ESCAPE)
		{
			sapp_quit();
		}
	}
}

// Open window
sapp_desc sokol_main(int argc, char* argv[]) {
	return (sapp_desc) {
		.width = 1280,
		.height = 720,
		.window_title = "NULL",
		.init_cb = init,
		.frame_cb = frame,
		.cleanup_cb = cleanup,
		.event_cb = event,
		.logger.func = slog_func,
	};
}