#include "pch.h"
#include "camera.h"
#include <algorithm>
#include "de2.h"

double rad(double degrees){
	return degrees * glm::pi<double>() / 180;
}
float map_range(float s, float a1, float a2, float b1, float b2) {
	return b1 + ((s-a1)*(b2-b1))/(a2-a1);
}

double get_sensivity_by_zoom(size_t zoom) {
	std::array<double, 19> sensivities = { 0.0040, 0.0035, 0.0017, 0.0010, 0.0005,
		/*5*/0.0004, 0.0002, 0.0001, 0.00005, 0.000020,
		/*10*/0.00001, 0.000005, 0.000001, 0.0000005, 0.0000025 };
	return sensivities[zoom];
}

//euler_angle_orbit
euler_angle_orbit::euler_angle_orbit() {
	zoom_ = 2;
}

glm::mat4 euler_angle_orbit::getview() {
	return glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -get_altitude(zoom_))) * glm::eulerAngleXYZ(-(float)pitch, 0.0f, (float)yaw);
}

glm::vec3 euler_angle_orbit::get_world_pos() {
	return glm::vec3(0.0, 0.0, -get_altitude(zoom_));
}

void euler_angle_orbit::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		ldown = true;
		glfwGetCursorPos(window, &lastx, &lasty);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		ldown = false;
	}
}
void euler_angle_orbit::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	if (ldown) {

		double sensivity = get_sensivity_by_zoom(zoom_);
		yaw -= (lastx - xpos) * sensivity;
		pitch = std::clamp(pitch + (lasty - ypos) * sensivity, glm::pi<double>() * 2 , glm::pi<double>() * 3);
		lastx = xpos;
		lasty = ypos;
	}
}
void euler_angle_orbit::mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset) {
	zoom_ = std::clamp(zoom_ + (size_t)yoffset, (size_t)2, (size_t)12);
}

double euler_angle_orbit::get_altitude(size_t zoom) {
	return 6378137.0f + get_altitude_base(zoom);
	//return 6378137.0 + 0.05 * 591657550.5 / std::pow(2, map_zoom - 1) / 2 * std::cos(rad(85.362 / 2)) / std::sin(rad(85.362 / 2));
}
double euler_angle_orbit::get_altitude_base(size_t zoom) {
	std::array<double, 19> altitudes = { 50000000, 30000000, 15000000, 7500000, 3750000,
		/*5*/1800000, 900000, 450000, 225000, 100000,
		/*10*/50000, 20000, 8000, 4000, 2000, 1000 };
	return altitudes[zoom];
	//return 6378137.0 + 0.05 * 591657550.5 / std::pow(2, map_zoom - 1) / 2 * std::cos(rad(85.362 / 2)) / std::sin(rad(85.362 / 2));
}