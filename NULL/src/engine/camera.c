#include "sokol_app.h"
#include "sokol_time.h"
#include "cglm/cglm.h"
#include "globals.h"

// Camera code based on https://learnopengl.com/Getting-started/Camera

static struct {
	vec3 position;
	vec3 direction;
	vec3 front;
	vec3 up;
	float yaw;
	float pitch;
	vec3 target; // direction vector camera is pointed at
	vec3 direction_space; // vector pointed back into the camera
	vec3 right; // right vector representing the x axis of camera space
	vec3 up_space; // up vector representing the y-axis of camera space
	mat4 view;
}camera;

float last_X, last_Y;
const float sensitivity = 0.1f;

void camera_init() {
	glm_vec3_copy((vec3) { 0.0f, 0.0f, 3.0f }, camera.position);
	glm_vec3_copy((vec3) { 0.0f, 0.0f, -1.0f }, camera.front);
	glm_vec3_copy((vec3) { 0.0f, 1.0f, 0.0f }, camera.up);
	glm_vec3_copy((vec3) { 0.0f, 0.0f, 0.0f }, camera.target);

	vec3 position_minus_target;
	glm_vec3_sub(camera.position, camera.target, position_minus_target);
	glm_normalize_to(position_minus_target, camera.direction_space);

	vec3 up = { 0.0f, 1.0f, 0.0f }; // an up vector in world space used to find right vector
	vec3 perpendicular;
	glm_cross(up, camera.direction_space, perpendicular);
	glm_normalize_to(perpendicular, camera.right);
	glm_cross(camera.direction_space, camera.right, camera.up_space);

	// Camera direction vector
	camera.yaw = -90.0f;
	camera.direction[0] = cos(glm_rad(camera.yaw)) * cos(glm_rad(camera.pitch));
	camera.direction[1] = sin(glm_rad(camera.pitch));
	camera.direction[2] = sin(glm_rad(camera.yaw)) * cos(glm_rad(camera.pitch));

	last_X = sapp_width() / 2.0f;
	last_Y = sapp_height() / 2.0f;
}

void camera_frame() {
	const float radius = 3.0f;
	float camX = sin(stm_sec(stm_since(start_time))) * radius;
	float camZ = cos(stm_sec(stm_since(start_time))) * radius;

	// glm_lookat((vec3) { camX, 0.0f, camZ}, (vec3) { 0.0f, 0.0f, 0.0f }, (vec3) { 0.0f, 1.0f, 0.0f }, camera.view);
	vec3 position_plus_front;
	glm_vec3_add(camera.position, camera.front, position_plus_front);
	glm_lookat(camera.position, position_plus_front, camera.up, camera.view);
}

void camera_input(const sapp_event* event) {
	const float camera_speed = 10.0f * delta_time;
	if (event->key_code == SAPP_KEYCODE_W) {
		vec3 front_times_speed;
		glm_vec3_scale(camera.front, camera_speed, front_times_speed);
		glm_vec3_add(camera.position, front_times_speed, camera.position);
	}
	if (event->key_code == SAPP_KEYCODE_S) {
		vec3 front_times_speed;
		glm_vec3_scale(camera.front, camera_speed, front_times_speed);
		glm_vec3_sub(camera.position, front_times_speed, camera.position);
	}
	if (event->key_code == SAPP_KEYCODE_A) {
		vec3 front_cross_up;
		glm_cross(camera.front, camera.up, front_cross_up);
		glm_normalize(front_cross_up);
		vec3 front_times_speed;
		glm_vec3_scale(front_cross_up, camera_speed, front_times_speed);
		glm_vec3_sub(camera.position, front_times_speed, camera.position);
	}
	if (event->key_code == SAPP_KEYCODE_D) {
		vec3 front_cross_up;
		glm_cross(camera.front, camera.up, front_cross_up);
		glm_normalize(front_cross_up);
		vec3 front_times_speed;
		glm_vec3_scale(front_cross_up, camera_speed, front_times_speed);
		glm_vec3_add(camera.position, front_times_speed, camera.position);
	}

	// Handle mouse
	if (event->type == SAPP_EVENTTYPE_MOUSE_MOVE) {
		if (!DEBUG_MODE) {
			float offset_x = event->mouse_dx;
			float offset_y =  -event->mouse_dy;
			last_X = event->mouse_x;
			last_Y = event->mouse_y;

			offset_x *= sensitivity;
			offset_y *= sensitivity;

			camera.yaw += offset_x;
			camera.pitch += offset_y;

			if (camera.pitch > 89.0f) camera.pitch = 89.0f;
			if (camera.pitch < -89.0f) camera.pitch = -89.0f;

			camera.direction[0] = cos(glm_rad(camera.yaw)) * cos(glm_rad(camera.pitch));
			camera.direction[1] = sin(glm_rad(camera.pitch));
			camera.direction[2] = sin(glm_rad(camera.yaw)) * cos(glm_rad(camera.pitch));
			glm_normalize_to(camera.direction, camera.front);
		}
	}
}

mat4* camera_get_view() {
	return &camera.view;
}