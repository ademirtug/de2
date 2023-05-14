#include "pch.h"
#include "camera.h"
#include <algorithm>


float map_range(float s, float a1, float a2, float b1, float b2) {
	return b1 + ((s-a1)*(b2-b1))/(a2-a1);
}

//euler_angle_orbit
euler_angle_orbit::euler_angle_orbit() {
	zoom_ = 1;
}
glm::mat4 euler_angle_orbit::getview() {
	return glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -get_altitude(zoom_)))
		* glm::eulerAngleXY((float)std::clamp(pitch, -glm::pi<double>()/2*0.85, glm::pi<double>() / 2 * 0.85), (float)yaw);
		//* glm::eulerAngleXY((float)pitch, (float)yaw);
}

glm::vec3 euler_angle_orbit::getpos() {
	auto cam = inverse(getview())[3];
	return cam;
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
		double sensivity = (0.00015 * (std::pow(2, 18 - zoom_) / 1000.f));
		yaw -= (lastx - xpos) * sensivity;
		pitch -= (lasty - ypos) * sensivity;

		lastx = xpos;
		lasty = ypos;
	}
}
void euler_angle_orbit::mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset) {
	zoom_ = std::clamp(zoom_ + yoffset, 1.0, 17.0);
}

double euler_angle_orbit::get_altitude(int map_zoom) {
	return 6.3781370f + std::pow(2, 18 - map_zoom) / 1000.f;
}