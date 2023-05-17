#pragma once

#include "framework.h"
#include "glm/glm.hpp"

struct GLFWwindow;

class camera {
protected:
	bool ldown = false;

public:
	virtual glm::mat4 getview() = 0;
	virtual glm::vec3 get_world_pos() = 0;
	virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) = 0;
	virtual void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) = 0;
	virtual void mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset) = 0;

	virtual double get_altitude(int mapzoom) = 0;
	size_t zoom_{ 1 }, fov{ 45 };
};

class euler_angle_orbit : public camera {
	double lastx{ 0 }, lasty{ 0 };
	double yaw{ 0 }, pitch{ 7.85 };
public:
	euler_angle_orbit();
	glm::mat4 getview();
	glm::vec3 get_world_pos();
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset);
	//glm::vec3 get_arcball_vector(int x, int y);

	double get_altitude(int map_zoom) override;

};