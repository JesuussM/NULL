#include "sokol_app.h"
#include "sokol_gfx.h"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "sokol_imgui.h"
#include "gui.h"
#include "renderer.h"


static bool show_demo = false;

void gui_init() 
{
	// Initalize ImGui
	simgui_setup(&(simgui_desc_t) {0});
}

void gui_show_window()
{
	simgui_new_frame(&(simgui_frame_desc_t) {
		.width = sapp_width(),
			.height = sapp_height(),
			.delta_time = sapp_frame_duration(),
			.dpi_scale = sapp_dpi_scale(),
	});

	// General gui window
	sg_pass_action* pass_action = renderer_get_pass_action();
	igText("Hello World!");
	igColorEdit3("clear color", &pass_action->colors[0].clear_value.r, 0);
	if (igButton("Demo Window", (ImVec2){.x = 100, .y = 20})) show_demo ^= 1;
	igText("Application average %.3f ms / frame (%.1f FPS)", 1000.f / igGetIO_Nil()->Framerate, igGetIO_Nil()->Framerate);
	igText("w: %d, h: %d, dpi_scale: %.1f", sapp_width(), sapp_height(), sapp_dpi_scale());

	// Demo gui
	if (show_demo) igShowDemoWindow(&show_demo);

	simgui_render();
}

void gui_input(const sapp_event* event)
{
	simgui_handle_event(event);
}

void gui_shutdown()
{
	simgui_shutdown();
}