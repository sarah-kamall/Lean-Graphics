#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <math.h>
// opengl functions are in driver
// use glad to load opengl functions

struct Vec3
{
    float x, y, z;
};
struct Color
{
    uint8_t r, g, b, a;
};
struct Vertex
{
    Vec3 position;
    Color color;
};

GLuint loadShader(const std::string path, GLenum shaderType)
{
    std::ifstream file(path);
    std::string sourceCode = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    const char *sourceCodeCStr = sourceCode.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &sourceCodeCStr, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *logStr = new char[length];
        glGetShaderInfoLog(shader, length, nullptr, logStr);
        std::cerr << "ERROR IN " << path << std::endl;
        std::cerr << logStr << std::endl;
        delete[] logStr;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

int main(int, char **)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initilize GLFW\n";
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello Triangle", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Error in window creation\n";
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to load gl\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }
    GLuint program = glCreateProgram();
    GLuint vs = loadShader("assets/shaders/simple.vert", GL_VERTEX_SHADER);
    GLuint fs = loadShader("assets/shaders/simple.frag", GL_FRAGMENT_SHADER);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(fs);
    glDeleteShader(vs);
    Vertex verices[4] = {
        {{-0.5, -0.5, 0.0}, {255, 200, 0, 255}},
        {{0.5, -0.5, 0.0}, {0, 50, 0, 255}},
        {{-0.5, 0.5, 0.0}, {0, 100, 0, 255}},
        {{0.5, 0.5, 0.0}, {255, 200, 0, 255}},
    };
    uint16_t elements[6] = {0, 1, 2, 3, 1, 2};
    GLuint vertex_array; // this is what knows the true logic of drawing on where
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    GLuint vertex_buffer; // this is just a container of data and its type indicates the proximity of memory to both GPU and CPU
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), verices, GL_STATIC_DRAW);

    GLuint element_buffer; // this is just a container of data and its type indicates the proximity of memory to both GPU and CPU
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint16_t), elements, GL_STATIC_DRAW);

    GLuint position_location = 0;
    glEnableVertexAttribArray(position_location);
    glVertexAttribPointer(position_location, 3, GL_FLOAT, false, sizeof(Vertex), 0);

    GLuint color_location = 1;
    glEnableVertexAttribArray(color_location);
    glVertexAttribPointer(color_location, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void *)(offsetof(Vertex, color))); // normalized divides by max(type)

    GLuint time_loc = glGetUniformLocation(program, "time");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    // glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();

        glClearColor(0.0, 0.0, 0.0, 1); // config
        glClear(GL_COLOR_BUFFER_BIT);   // apply config to backbuffer
        glUseProgram(program);

        glBindVertexArray(vertex_array);
        glUniform1f(time_loc, time);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void *)0);
        glfwSwapBuffers(window); // swap back with front buffer

        glfwPollEvents();
    }
    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
// GLuint : unsigned int :: all types are integer and function return id indicating what type of certain obj is
// what are buffers ???
// when I don't want to pass anything from CPU and GPU like having some kind of shared memiory between shared buffer
