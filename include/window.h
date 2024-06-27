#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "window_manager.h"

class Window {
public:

private:
	WindowManager* window_manager_;
	GLFWwindow* glfw_window_;
	int width_;
	int height_;

public: 
	static Window* Create(WindowManager& window_manager, int width, int height, const std::string& name);
	static Window* Create(WindowManager& window_manager, int width, int height);

	void Render();
	void SetName(const std::string& new_name) const;
	~Window();
private:
	Window(WindowManager& window_manager, int width, int height, std::string name);

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);


};


#endif // !WINDOW

