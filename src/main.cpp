#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "application.h"
#include "event_manager.h"
#include "window.h"

constexpr int kWindowHeight = 640;
constexpr int kWindowWidth = 820;

EventManager event_manager;

int main() {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Application::Start();
    
    //Start everything up
    glfwInit();
    event_manager.StartUp();

    auto window = std::unique_ptr<Window>(Window::Create(kWindowWidth, kWindowHeight, "The Powder Game"));
    
    //Actual loop

    while(Application::IsRunning() && !glfwWindowShouldClose(&window->GetNativeWindow())) {
        window->Render();
        event_manager.Update();
    }


    //Shut everything down
    event_manager.ShutDown();
	return 0;
}