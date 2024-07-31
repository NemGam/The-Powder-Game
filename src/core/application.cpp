#include <iostream>
#include <GLFW/glfw3.h>

#include "application.h"

namespace powder_sim {
	bool Application::is_running_;

	void Application::Start() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, false);
		is_running_ = true;
	}

	bool Application::IsRunning() {
		return is_running_;
	}


	void Application::Quit() {
		std::cout << "Quitting\n";
		is_running_ = false;
	}
}


