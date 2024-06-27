#include"window.h"
#include<iostream>

Window::Window(WindowManager& window_manager, int width, int height, std::string name)
    :width_(width), height_(height)
{
    window_manager_ = &window_manager;
    glfw_window_ = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::SetName(const std::string& new_name) const{
    glfwSetWindowTitle(glfw_window_, new_name.c_str());
}


Window* Window::Create(WindowManager& window_manager, int width, int height) {
    return Create(window_manager, width, height, "Main Window");
}

Window* Window::Create(WindowManager& window_manager, int width, int height, const std::string& name) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = new Window(window_manager, width, height, name);

    if (window->glfw_window_ == nullptr) {
        std::cerr << "Failed to create GLFW window\n";
        return nullptr;
    }

    glfwMakeContextCurrent(window->glfw_window_);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        return nullptr;
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window->glfw_window_, FramebufferSizeCallback);
    return window;
}

void Window::Render() {

    if (!glfwWindowShouldClose(glfw_window_))
    {
        glfwSwapBuffers(glfw_window_);
        glfwPollEvents();
    }
    else {
        window_manager_->DestroyWindow();
    }
}

Window::~Window() {
    
    glfwDestroyWindow(glfw_window_);
}
