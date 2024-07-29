#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"

#include <glad/glad.h>

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
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

unsigned int Shader::CreateShader(const std::string& vertex_shader, const std::string& fragment_shader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


ShaderSource Shader::ParseShader(const std::string& filepath) {
	enum class ShaderType {
		kNone = -1, kVertex = 0, kFragment = 1
	};


	std::ifstream stream(filepath);
	if (!stream) {
		std::cerr << "Failed to open shader at " << filepath << "\n";
		return { "", "" };
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

	return { ss[0].str(), ss[1].str() };
}

Shader::Shader(const std::string& filepath) {
	ShaderSource source = ParseShader(filepath);

	unsigned int shader = CreateShader(source.vertex, source.fragment);

	glUseProgram(shader);

	glDeleteProgram(shader);

}

