#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "shader.h"
#include "core/application.h"
#include "core/window.h"
#include "core/input_manager.h"
#include "core/random.h"

#include "simulation.h"

constexpr int kWindowHeight = 640;
constexpr int kWindowWidth = 820;


void ProcessInput() {
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


constexpr int kTextureWidth = 350;
constexpr int kTextureHeight = 350;


int main() {
	//Start everything up
	Application::Start();
	auto window = std::unique_ptr<Window>(Window::Create(kWindowWidth, kWindowHeight, "The Powder Game"));
	InputManager::Initialize(&window->GetNativeWindow());



	std::cout << glGetString(GL_VERSION) << "\n";


	float vertices[] = {
		//Poses         //Texture poses
		1.0f, 1.0f, 1.0f, 1.0f, // 0
		1.0f, -1.0f, 1.0f, 0.0f, // 1
		-1.0f, -1.0f, 0.0f, 0.0f, // 2
		-1.0f, 1.0f, 0.0f, 1.0f, // 3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	//Initialize OpenGL stuff
	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr); //position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); //texPos
	glEnableVertexAttribArray(1);

	//Shader
	Shader main_shader = Shader("res/shaders/basic.shader");

	//CREATING TEXTURE

	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	Simulation simulation(window.get(), kTextureWidth, kTextureHeight);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, kTextureWidth,
	             kTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	             simulation.GetMatrix().GetColorData()->data());

	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	simulation.Start();

	float last_frame = 0.0f;
	float last_render_frame = 0.0f;

	

	//Actual loop
	while (Application::IsRunning() && !glfwWindowShouldClose(&window->GetNativeWindow())) {
		float currentFrame = static_cast<float>(glfwGetTime());
		float deltaTime = currentFrame - last_frame;
		last_frame = currentFrame;

		ProcessInput();


		simulation.Update(deltaTime);
		std::cout << static_cast<int>(1 / (currentFrame - last_render_frame)) << '\n';
		glfwPollEvents();
		//if (currentFrame - lastRenderFrame >= 1/60.0f)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vao);
			glBindTexture(GL_TEXTURE_2D, texture);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);

			glfwSwapBuffers(&window->GetNativeWindow());


			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, kTextureWidth, kTextureHeight, GL_RGBA, GL_UNSIGNED_BYTE,
			                simulation.GetMatrix().GetColorData()->data());

			last_render_frame = currentFrame;
		}
	}

	//Clean up
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	
	glfwTerminate();
	return 0;
}
