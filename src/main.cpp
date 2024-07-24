#include <array>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "application.h"
#include "event_manager.h"
#include "window.h"
#include <fstream>
#include <sstream>

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



constexpr int textureWidth = 100;
constexpr int textureHeight = 100;

static GLubyte checkImage[textureWidth][textureHeight][4];

void makeCheckImage()
{
	for (int i = 0; i < textureWidth; i++) {
        for (int j = 0; j < textureHeight; j++) {

            checkImage[i][j][0] = 255;//count % 255;
            checkImage[i][j][1] = 0;//(count / 255) % 255;
            checkImage[i][j][2] = 0;//(count / 255 / 255) % 255;
            checkImage[i][j][3] = 1;//(count / 255 / 255) % 255;
        }
    }
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


    float texCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };

    float vertices[] = {
        //Poses         //Texture poses
         1.0f,  1.0f,   1.0f, 1.0f,// 0
         1.0f, -1.0f,   1.0f, 0.0f,// 1
        -1.0f, -1.0f,   0.0f, 0.0f,// 2
    	-1.0f,  1.0f,   0.0f, 1.0f,// 3
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
    std::cout << shader << std::endl;

    makeCheckImage();

    unsigned int texture;   
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Simulation simulation(textureWidth, textureHeight);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth,
        textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
        simulation.GetMatrix().GetColorData()->data());



    glUseProgram(shader);

    simulation.Start();

    int count = 0;
    //Actual loop
    while(Application::IsRunning() && !glfwWindowShouldClose(&window->GetNativeWindow())) {
        count++;
        event_manager.ProcessInput(&window->GetNativeWindow());

        simulation.Update();


        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(&window->GetNativeWindow());

        
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureWidth, textureHeight, GL_RGBA, GL_UNSIGNED_BYTE, simulation.GetMatrix().GetColorData()->data());
        glfwPollEvents();
    }

    //Clean up
    //glDeleteFramebuffers(1, &fbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shader);
    glfwTerminate();
	return 0;
}