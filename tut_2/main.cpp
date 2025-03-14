#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <math.h>
// opengl functions are in driver
// use glad to load opengl functions
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

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);

    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();

        glClearColor(sinf(time) * 0.5 + 0.3, sinf(time + 1) * 0.5 + 0.5, sinf(time + 2) + 0.7, 1); // config
        glClear(GL_COLOR_BUFFER_BIT);                                                              // apply config to backbuffer
        glUseProgram(program);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window); // swap back with front buffer

        glfwPollEvents();
    }
    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// GLuint load_shader(const std::string &path, GLenum shader_type)
// {
//     std::ifstream file(path);
//     std::string sourceCode = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
//     const char *sourceCodeCStr = sourceCode.c_str();

//     GLuint shader = glCreateShader(shader_type);
//     glShaderSource(shader, 1, &sourceCodeCStr, nullptr);
//     glCompileShader(shader);

//     GLint status;
//     glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
//     if (!status)
//     {
//         GLint length;
//         glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
//         char *logStr = new char[length];
//         glGetShaderInfoLog(shader, length, nullptr, logStr);
//         std::cerr << "ERROR IN " << path << std::endl;
//         std::cerr << logStr << std::endl;
//         delete[] logStr;
//         glDeleteShader(shader);
//         return 0;
//     }

//     return shader;
// }

// int main()
// {

//     if (!glfwInit())
//     {
//         std::cerr << "Failed to initialize GLFW\n";
//         exit(1);
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     GLFWwindow *window = glfwCreateWindow(640, 480, "Hello Triangle", nullptr, nullptr);

//     if (!window)
//     {
//         std::cerr << "Failed to create Window\n";
//         glfwTerminate();
//         exit(1);
//     }

//     glfwMakeContextCurrent(window);
//     if (!gladLoadGL((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cerr << "Failed to load OpenGL\n";
//         glfwDestroyWindow(window);
//         glfwTerminate();
//         exit(1);
//     }

//     GLuint program = glCreateProgram();
//     GLuint vs = load_shader("assets/shaders/simple.vert", GL_VERTEX_SHADER);
//     GLuint fs = load_shader("assets/shaders/simple.frag", GL_FRAGMENT_SHADER);
//     glAttachShader(program, vs);
//     glAttachShader(program, fs);
//     glLinkProgram(program);

//     glDeleteShader(vs);
//     glDeleteShader(fs);

//     GLuint vertex_array;
//     glGenVertexArrays(1, &vertex_array);

//     while (!glfwWindowShouldClose(window))
//     {
//         float time = (float)glfwGetTime();
//         glClearColor(
//             0.5 * sinf(time) + 0.5,
//             0.5 * sinf(time + 1.0) + 0.5,
//             0.5 * sinf(time + 2.0) + 0.5,
//             1.0);
//         glClear(GL_COLOR_BUFFER_BIT);

//         glUseProgram(program);
//         glBindVertexArray(vertex_array);
//         glDrawArrays(GL_TRIANGLES, 0, 3);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glDeleteProgram(program);

//     glfwDestroyWindow(window);
//     glfwTerminate();

//     return 0;
// }
