#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "application.h"
#include "event_manager.h"
#include "window.h"
#include <fstream>
#include <sstream>
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

    return { ss[0].str(), ss[1].str()};
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

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    
    //Start everything up
    Application::Start();

    auto window = std::unique_ptr<Window>(Window::Create(kWindowWidth, kWindowHeight, "The Powder Game"));
    EventManager event_manager = EventManager();

    std::cout << glGetString(GL_VERSION) << "\n";

    

    float vertices[] = {
        //Poses         //Colors
        0.5f, -0.5f,   1.0f, 0.0f, 0.0f,// 0
        -0.5f, -0.5f,     0.0f, 1.0f, 0.0f,// 1
        0.0f, 0.5f,    0.0f, 0.0f, 1.0f,// 2
    };

    unsigned int indices[] = {
	    0, 1, 2
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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr); //position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float))); //color
    glEnableVertexAttribArray(1);

    //Unbinding buffers to avoid accidental modification
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ShaderSource source = ParseShader("res/shaders/basic.shader");

	unsigned int shader = CreateShader(source.vertex, source.fragment);

    //Actual loop
    while(Application::IsRunning() && !glfwWindowShouldClose(&window->GetNativeWindow())) {

        event_manager.ProcessInput(&window->GetNativeWindow());
        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader, "color");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(&window->GetNativeWindow());

        glfwPollEvents();
    }

    //Clean up
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shader);
    glfwTerminate();
	return 0;
}