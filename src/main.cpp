#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "shader.h"
#include "core/application.h"
#include "rendering/window.h"
#include "core/input_manager.h"

#include "simulation.h"
#include "rendering/mesh.h"

constexpr int kWindowHeight = 640;
constexpr int kWindowWidth = 820;

constexpr int kTextureWidth = 350;
constexpr int kTextureHeight = 350;


int main() {
	//Start everything up
	Application::Start();
	auto window = std::unique_ptr<Window>(Window::Create(kWindowWidth, kWindowHeight, "The Powder Sim"));
	InputManager::Initialize(&window->GetNativeWindow());


	std::cout << glGetString(GL_VERSION) << "\n";


	std::vector vertices = {
		Vertex({1.0f, 1.0f}, {1.0f, 1.0f}), // 0
		Vertex({1.0f, -1.0f}, {1.0f, 0.0f}), // 1
		Vertex({-1.0f, -1.0f}, {0.0f, 0.0f}), // 2
		Vertex({-1.0f, 1.0f}, {0.0f, 1.0f}), // 3
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	Simulation simulation(window.get(), kTextureWidth, kTextureHeight);

	Texture main_tex(kTextureWidth, kTextureHeight);
	main_tex.SetDynamicData(simulation.GetMatrix().GetColorData());
	
	Mesh screen_quad(vertices, indices, main_tex);

	//Shader
	Shader main_shader("res/shaders/basic.shader");


	

	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	simulation.Start();

	float last_frame = 0.0f;
	float last_render_frame = 0.0f;

	//Actual loop
	while (Application::IsRunning() && !glfwWindowShouldClose(&window->GetNativeWindow())) {
		float current_frame = static_cast<float>(glfwGetTime());
		float delta_time = current_frame - last_frame;
		last_frame = current_frame;

		window->Update();
		simulation.Update(delta_time);
		std::cout << static_cast<int>(1 / (current_frame - last_render_frame)) << '\n';
		glfwPollEvents();
		//if (current_frame - last_render_frame >= 1/60.0f)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			screen_quad.Render(main_shader);


			glfwSwapBuffers(&window->GetNativeWindow());


			/*glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, kTextureWidth, kTextureHeight, GL_RGBA, GL_UNSIGNED_BYTE,
			                simulation.GetMatrix().GetColorData()->data());*/

			last_render_frame = current_frame;
		}
	}

	//Clean up
	glfwTerminate();
	return 0;
}
