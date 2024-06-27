#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "application.h"
#include "event_manager.h"
#include "window_manager.h"



EventManager event_manager;
WindowManager window_manager;

int main() {

    Application::Start();

    //Start everything up
    glfwInit();
    event_manager.StartUp();
    window_manager.StartUp();


    
    //Actual loop
    window_manager.GetCurrentWindow().SetName("The Powder Game");

    while(Application::IsRunning()) {
        window_manager.Update();
        event_manager.Update();
    }


    //Shut everything down
    window_manager.ShutDown();
    event_manager.ShutDown();
	return 0;
}