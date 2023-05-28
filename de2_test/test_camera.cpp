#include "test_camera.h"
test_camera::test_camera() {
	zoom_ = 10;
}

glm::mat4 test_camera::getview() {
	return glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -get_altitude(zoom_))) * glm::eulerAngleXYZ(-(float)pitch, (float)yaw, 0.0f );
}

glm::vec3 test_camera::get_world_pos() {
	return glm::vec3(0.0, 0.0, -get_altitude(zoom_));
}

void test_camera::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		ldown = true;
		glfwGetCursorPos(window, &lastx, &lasty);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		ldown = false;
	}
}
void test_camera::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	if (ldown) {
		double sensivity = zoom_ != 0 ? (20 - zoom_) * 0.0004 : 0.0004;
		yaw -= (lastx - xpos) * sensivity ;
		pitch += (lasty - ypos) * sensivity;
		lastx = xpos;
		lasty = ypos;
	}
}

void test_camera::mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset) {
	zoom_ = std::clamp(zoom_ + yoffset, 1.0, 20.0);
}

double test_camera::get_altitude(int map_zoom) {
	return (20 - map_zoom) * 1;
}