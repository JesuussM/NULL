#include "renderer.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_log.h"

static struct
{
	float rx, ry;
	sg_pipeline pipeline;
	sg_bindings bindings;
} state;

// static vs_params_t compute_vsparams(float rx, float ry);

void renderer_init()
{
}

void renderer_shutdown()
{
}