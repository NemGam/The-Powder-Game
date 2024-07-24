#ifndef WINDOW_H
#define WINDOW_H
#include <memory>
#include <string>
#include <glad/glad.h>
#include <vector>
#include <GLFW/glfw3.h>

struct DestroyGLFWWin {

		void operator()(GLFWwindow* ptr) {
			glfwDestroyWindow(ptr);
		}
	};

class Window {
public:

private:
	std::unique_ptr<GLFWwindow, DestroyGLFWWin> glfw_window_;
	std::vector<std::vector<std::vector<unsigned int>>> data_;
	int width_;
	int height_;

public: 
	static Window* Create(int width, int height, const std::string& name);
	static Window* Create(int width, int height);

	GLFWwindow& GetNativeWindow();
	void Render();
	void SetTitle(const std::string& new_name);
	~Window();
private:
	Window(int width, int height, std::string name);

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);


};


#endif // !WINDOW

