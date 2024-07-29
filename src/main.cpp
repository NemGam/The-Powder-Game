#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "core/application.h"
#include "core/window.h"
#include "core/input_manager.h"
#include "core/random.h"

#include "simulation.h"

constexpr int kWindowHeight = 640;
constexpr int kWindowWidth = 820;

struct ShaderSource {
	std::string vertex;
	std::string fragment;
};

static ShaderSource ParseShader(const std::string& filepath) {
	enum class ShaderType {
		kNone = -1, kVertex = 0, kFragment = 1
	};


	std::ifstream stream(filepath);
	if (!stream) {
		std::cerr << "Failed to open shader at " << filepath << "\n";
		return {"", ""};
	}

	ShaderType type = ShaderType::kNone;

	std::string line;
	std::stringstream ss[2];
	while (std::getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::kVertex;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::kFragment;
			}
		}
		else {
			ss[static_cast<int>(type)] << line << "\n";
		}
	}

	return {ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result) {
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char* message = static_cast<char*>(alloca(len * sizeof(char)));
		glGetShaderInfoLog(id, len, &len, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << "\n";
		std::cout << message << "\n";
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


void ProcessInput() {
	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_ESCAPE)) {
		Application::Quit();
	}

	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_F1)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_F2)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}


constexpr int textureWidth = 350;
constexpr int textureHeight = 350;

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


	ShaderSource source = ParseShader("res/shaders/basic.shader");

	unsigned int shader = CreateShader(source.vertex, source.fragment);

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

	Simulation simulation(window.get(), textureWidth, textureHeight);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth,
	             textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	             simulation.GetMatrix().GetColorData()->data());

	glUseProgram(shader);
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


			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureWidth, textureHeight, GL_RGBA, GL_UNSIGNED_BYTE,
			                simulation.GetMatrix().GetColorData()->data());

			last_render_frame = currentFrame;
		}
	}

	//Clean up
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}
