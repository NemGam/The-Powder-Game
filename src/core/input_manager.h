#ifndef input_manager_H
#define input_manager_H

#include <unordered_map>

#include "core/window.h"

class InputManager {
public:
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;


	static void Initialize(const GLFWwindow* window);


	static InputManager& GetInstance();
	std::tuple<double, double> GetMousePosition() const;
	std::tuple<double, double> GetMouseScroll() const;
	static bool IsKeyDown(int key);
	bool IsMouseButtonDown(int button);

private:
	InputManager();

	~InputManager() = default;


	static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
	static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

	std::unordered_map<int, bool> key_states_;
	std::unordered_map<int, bool> mouse_buttons_states_;
	double mouse_x_, mouse_y_;
	double mouse_scroll_x_, mouse_scroll_y_;
};
#endif // input_manager_H
