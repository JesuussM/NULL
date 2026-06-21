#define SOKOL_LOG_IMPL
#include "sokol_app.h"
#include "sokol_log.h"
#include "renderer.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "triangle.glsl.h"

#include "cglm/cglm.h"

static struct
{
	float rx, ry;
	sg_pipeline pipeline;
	sg_bindings bindings;
	sg_pass_action pass_action;
} state;

void renderer_init()
{
	// Initialize graphics
	sg_setup(&(sg_desc) {
		.environment = sglue_environment(),
		.logger.func = slog_func,
	});

	// Vertex buffer
	float vertices[] = {
		// positions            // colors
		 0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
	};

	state.bindings.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc) {
		.data = SG_RANGE(vertices),
		.label = "vertex-buffer"
	});

	// Create shader
	sg_shader shader = sg_make_shader(triangle_shader_desc(sg_query_backend()));

	// Create pipeline object
	state.pipeline = sg_make_pipeline(&(sg_pipeline_desc) {
		.shader = shader,
			.layout = {
				.attrs = {
					[ATTR_triangle_position].format = SG_VERTEXFORMAT_FLOAT3,
					[ATTR_triangle_color0].format = SG_VERTEXFORMAT_FLOAT4
				}
		},
		.label = "triangle-pipeline"
	});
	
	// Pass action to make framebuffer a light blue color
	state.pass_action = (sg_pass_action){
		.colors[0] = {
			.load_action = SG_LOADACTION_CLEAR,
			.clear_value = { 0.2f, 0.4f, 0.6f, 1.0f },
		}
	};
}

void renderer_draw() {
	// Rotate Triangle
	state.rx += 1.0f * sapp_frame_duration();
	mat4 proj, view, model, mvp;
	glm_perspective(glm_rad(60.0f), (float)sapp_width() / (float)sapp_height(), 0.01f, 100.0f, proj);
	glm_lookat((vec3) { 0.0f, 0.0f, 2.5f }, (vec3) { 0.0f, 0.0f, 0.0f }, (vec3) { 0.0f, 1.0f, 0.0f }, view);
	glm_mat4_identity(model);
	glm_rotate_y(model, state.rx, model);

	glm_mat4_mul(view, model, mvp);
	glm_mat4_mul(proj, mvp, mvp);

	sg_begin_pass(&(sg_pass) {
		.action = state.pass_action,
		.swapchain = sglue_swapchain()
	});
	sg_apply_pipeline(state.pipeline);
	sg_apply_bindings(&state.bindings);
	sg_apply_uniforms(UB_mvp_block, &SG_RANGE(mvp));
	sg_draw(0,3,1);
}

sg_pass_action* renderer_get_pass_action()
{
	return &state.pass_action;
}