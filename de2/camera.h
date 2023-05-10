#pragma once

#include "framework.h"
#include "glm/glm.hpp"

struct GLFWwindow;

class camera {
protected:
	bool ldown = false;

public:
	virtual glm::mat4 getview() = 0;
	virtual glm::vec3 getpos() = 0;
	virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) = 0;
	virtual void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) = 0;
	virtual void mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset) = 0;

	virtual double get_altitude(int mapzoom) = 0;
};


class euler_orbit : public camera {
	double distance_{ 0 };
	double mydiff = { 0.00001 };
	double lastx{ 0 }, lasty{ 0 };
	double yaw{ 0 }, pitch{ 0 };
	double hyp1{ 0 }, hyp2{ 0 };
public:
	euler_orbit();
	glm::mat4 getview();
	glm::vec3 getpos();
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset);
};

class euler_angle_orbit : public camera {
	double mydiff = { 0.00001 };
	double lastx{ 0 }, lasty{ 0 };
	double yaw{ 0 }, pitch{ 0 }, d{ 0 }, c{ 0 };
	double hyp1{ 0 }, hyp2{ 0 }, cur_mx{ 0 }, cur_my{ 0 };
	size_t zoom_{ 1 };
public:
	euler_angle_orbit();
	glm::mat4 getview();
	glm::vec3 getpos();
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset);
	//glm::vec3 get_arcball_vector(int x, int y);

	double get_altitude(int map_zoom) override;
};