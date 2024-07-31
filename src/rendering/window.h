#ifndef WINDOW_H
#define WINDOW_H
#include <memory>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>

namespace powder_sim
{
	struct DestroyGLFWWin {
		void operator()(GLFWwindow* ptr) const {
			glfwDestroyWindow(ptr);
		}
	};

	class Window {
	public:
		static Window* Create(int width, int height, const std::string& name);
		static Window* Create(int width, int height);


		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window&& operator=(Window&&) = delete;

		~Window();


		[[nodiscard]] GLFWwindow& GetNativeWindow() const;
		[[nodiscard]] int GetWidth() const;
		[[nodiscard]] int GetHeight() const;
		void Update();
		void SetTitle(const std::string& new_name);

	private:
		Window(int width, int height, const std::string& name);


		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

		std::unique_ptr<GLFWwindow, DestroyGLFWWin> glfw_window_;
		std::vector<std::vector<std::vector<unsigned int>>> data_;
		int width_;
		int height_;
	};
}

#endif // !WINDOW

