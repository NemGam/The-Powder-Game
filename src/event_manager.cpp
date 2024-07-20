#include "event_manager.h"
#include "application.h"

void EventManager::ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		Application::Quit();

	if (glfwGetKey(window, GLFW_KEY_F1)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (glfwGetKey(window, GLFW_KEY_F2)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}



