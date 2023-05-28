#pragma once

#include <algorithm>
#include "../camera.h"
#include "../de2.h"


class test_camera : public camera {
	double lastx{ 0 }, lasty{ 0 };
	double yaw{ 0 }, pitch{ 0 };
public:
	test_camera();

	glm::mat4 getview();
	glm::vec3 get_world_pos();

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset);
	double get_altitude(int map_zoom) override;
};

//test_camera
