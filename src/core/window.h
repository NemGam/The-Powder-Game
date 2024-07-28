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
	static Window* Create(int width, int height, const std::string& name);
	static Window* Create(int width, int height);


	~Window();


	GLFWwindow& GetNativeWindow();
	void Render();
	void SetTitle(const std::string& new_name);
	[[nodiscard]] int GetWidth() const;
	[[nodiscard]] int GetHeight() const;

private:
	Window(int width, int height, const std::string& name);


	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);


	std::unique_ptr<GLFWwindow, DestroyGLFWWin> glfw_window_;
	std::vector<std::vector<std::vector<unsigned int>>> data_;
	int width_;
	int height_;
};


#endif // !WINDOW

