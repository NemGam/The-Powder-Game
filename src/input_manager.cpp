#include "input_manager.h"

#include <iostream>


void InputManager::Initialize(const GLFWwindow* window) {
	auto* win = const_cast<GLFWwindow*>(window);
	glfwSetMouseButtonCallback(win, MouseClickCallback);
	glfwSetKeyCallback(win, KeyboardCallback);
	glfwSetScrollCallback(win, MouseScrollCallback);
	glfwSetCursorPosCallback(win, CursorPosCallback);
}

InputManager& InputManager::GetInstance() {
	static InputManager instance;
	return instance;
}


std::tuple<double, double> InputManager::GetMousePosition() const {
	return { mouse_x_, mouse_y_ };
}

std::tuple<double, double> InputManager::GetMouseScroll() const {
	return { mouse_scroll_x_, mouse_scroll_y_ };
}

bool InputManager::IsKeyDown(int key) {
	auto it = key_states_.find(key);

	if (it != key_states_.end())
		return it->second;

	return false;
}

bool InputManager::IsMouseButtonDown(int button) {
	
	auto it = mouse_buttons_states_.find(button);

	if (it != mouse_buttons_states_.end())
		return it->second;

	return false;
}

InputManager::InputManager() :
	mouse_x_(0),
	mouse_y_(0),
	mouse_scroll_x_(0),
	mouse_scroll_y_(0)
{}

void InputManager::MouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		GetInstance().mouse_buttons_states_[button] = true;
	}
	else if (action == GLFW_RELEASE) {
		GetInstance().mouse_buttons_states_[button] = false;
	}
}

void InputManager::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	GetInstance().mouse_scroll_x_ = xoffset;
	GetInstance().mouse_scroll_y_ = yoffset;
}

void InputManager::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		GetInstance().key_states_[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		GetInstance().key_states_[key] = false;
	}
}

void InputManager::CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	//std::cout << xpos << " " << ypos << '\n';
	GetInstance().mouse_x_ = xpos;
	GetInstance().mouse_y_ = ypos;
}



