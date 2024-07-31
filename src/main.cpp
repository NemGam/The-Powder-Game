#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "rendering/shader.h"
#include "rendering/window.h"
#include "rendering/mesh.h"

#include "core/application.h"
#include "core/input_manager.h"

#include "simulation.h"

constexpr int kWindowHeight = 820;
constexpr int kWindowWidth = 1280;

constexpr int kGridWidth = 400;
constexpr int kGridHeight = 400;

using namespace powder_sim;

int main() {
	//Start everything up
	Application::Start();

	{
		auto window = std::unique_ptr<Window>(Window::Create(kWindowWidth, kWindowHeight, "The Powder Sim"));
		InputManager::Initialize(&window->GetNativeWindow());

		std::cout << glGetString(GL_VERSION) << "\n";

		

		Simulation simulation(window.get(), kGridWidth, kGridHeight);

		Texture main_tex(kGridWidth, kGridHeight);
		main_tex.SetDynamicData(simulation.GetMatrix().GetColorData());

		Mesh screen_quad(
			//Vertices
			{
				//Positions        //Texture coords
				Vertex({  1.0f,  1.0f }, { 1.0f, 1.0f }), // 0
				Vertex({  1.0f, -1.0f }, { 1.0f, 0.0f }), // 1
				Vertex({ -1.0f, -1.0f }, { 0.0f, 0.0f }), // 2
				Vertex({ -1.0f,  1.0f }, { 0.0f, 1.0f }), // 3
			},
			//Indices
			{ 
			  2, 1, 0,
			  0, 3, 2
			},
			//Texture
			main_tex
		);

		//Shader
		Shader main_shader("res/shaders/basic.shader");

		simulation.Start();

		float last_frame = 0.0f;
		float last_render_frame = 0.0f;

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		//Actual loop
		while (Application::IsRunning() && !glfwWindowShouldClose(&window->GetNativeWindow())) {
			float current_frame = static_cast<float>(glfwGetTime());
			float delta_time = current_frame - last_frame;
			last_frame = current_frame;

			window->Update();
			simulation.Update(delta_time);
			std::cout << static_cast<int>(1 / (current_frame - last_render_frame)) << '\r';
			glfwPollEvents();
			//if (current_frame - last_render_frame >= 1/60.0f)
			{
				glClear(GL_COLOR_BUFFER_BIT);
				screen_quad.Render(main_shader);

				glfwSwapBuffers(&window->GetNativeWindow());


				last_render_frame = current_frame;
			}
		}


		//Clean up
		glDeleteProgram(main_shader.GetId());
	}

	glfwTerminate();
	return 0;
}
