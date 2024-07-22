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



constexpr int textureWidth = 100;
constexpr int textureHeight = 128;

static GLubyte checkImage[textureWidth][textureHeight][3];

void makeCheckImage()
{
    int count = 0;
	for (int i = 0; i < textureWidth; i++) {
        for (int j = 0; j < textureHeight; j++) {

            checkImage[i][j][0] = 255;//count % 255;
            checkImage[i][j][1] = 0;//(count / 255) % 255;
            checkImage[i][j][2] = 0;//(count / 255 / 255) % 255;
            count += 2;
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
        //Poses         //Colors            //Texture poses
         1.0f,  1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,// 0
         1.0f, -1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,// 1
        -1.0f, -1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,// 2
    	-1.0f,  1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,// 3
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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr); //position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float))); //color
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float))); //tex pos
    glEnableVertexAttribArray(2);


    ShaderSource source = ParseShader("res/shaders/basic.shader");

	unsigned int shader = CreateShader(source.vertex, source.fragment);

    //CREATING TEXTURE


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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth,
        textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
        checkImage);


    //glBindTexture(GL_TEXTURE_2D, 0);
    //Unbinding buffers to avoid accidental modification
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);


    //unsigned int fbo;
    //glGenFramebuffers(1, &fbo);
    //glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    ////glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(shader);

    std::cerr << glGetError() << '\n';

    int count = 0;
    //Actual loop
    while(Application::IsRunning() && !glfwWindowShouldClose(&window->GetNativeWindow())) {

        event_manager.ProcessInput(&window->GetNativeWindow());

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(&window->GetNativeWindow());

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