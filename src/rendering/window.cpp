#include <iostream>
#include <glad/glad.h>

#include"window.h"

#include "core/application.h"
#include "core/input_manager.h"


Window::Window(int width, int height, const std::string& name) :
	data_(height, std::vector(width, std::vector<unsigned int>(3, 0))),
	width_(width), height_(height)
{
    glfw_window_.reset(glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr));
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::SetTitle(const std::string& new_name){
    glfwSetWindowTitle(glfw_window_.get(), new_name.c_str());
}

int Window::GetWidth() const {
    return width_;
}

int Window::GetHeight() const {
    return height_;
}


Window* Window::Create(int width, int height) {
    return Create(width, height, "Main Window");
}

Window* Window::Create(int width, int height, const std::string& name) {
    

    auto window = new Window(width, height, name);

    if (window->glfw_window_ == nullptr) {
        std::cerr << "Failed to create GLFW window\n";
        return nullptr;
    }

    glfwMakeContextCurrent(window->glfw_window_.get());


    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        return nullptr;
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window->glfw_window_.get(), FramebufferSizeCallback);
    return window;
}

GLFWwindow& Window::GetNativeWindow() const {
    return *glfw_window_;
}

void Window::Update() {
    if (InputManager::IsKeyDown(GLFW_KEY_ESCAPE)) {
        Application::Quit();
    }

    if (InputManager::IsKeyDown(GLFW_KEY_F1)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (InputManager::IsKeyDown(GLFW_KEY_F2)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

Window::~Window() {
    std::cout << "Destroying window!\n";
}
