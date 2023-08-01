#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Matrix.h"

std::string read_shader_source(const std::string& filePath) {
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cout << "Error failed to open shader file" << std::endl;
        return "";
    }

    std::string sourceCode;
    std::string line;
    while (getline(fileStream, line)) {
        sourceCode += line + "\n";
    }

    fileStream.close();
    return sourceCode;
}

static unsigned int compile_shader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* errorMessage = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, errorMessage);
        
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << errorMessage << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int create_shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = compile_shader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compile_shader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

// void create_projection_matrix(float* projectionMatrix, float fov, float aspect, float near, float far)
// {
//     for (int i = 0; i < 16; i++)
//     {
//         projectionMatrix[i] = 0.0f;
//     }

//     projectionMatrix[0] = 1.0f/(aspect*tanf((fov*0.5f*3.1415)/180.0f));
//     projectionMatrix[5] = 1.0f/tanf((fov*0.5f*3.1415)/180.0f);
//     projectionMatrix[10] = -(far + near)/(far - near);
//     projectionMatrix[11] = -1.0f;
//     projectionMatrix[14] = -(far * near)/(far-near);
// }

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "Error loading GLFW!" << std::endl;
    }

    window = glfwCreateWindow(screenWidth, screenHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error loading GLEW!" << std::endl;
    }

    float vertices[12] = {-0.5f, -0.5f, -2.0f, 1.0f,
                           0.0f,  0.5f, -10.0f, 1.0f,
                           0.5f, -0.5f, -2.0f, 1.0f};

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    std::string vertexShaderSource = read_shader_source(std::string("shaders/vertex_shader.glsl"));
    std::string fragmentShaderSource = read_shader_source(std::string("shaders/fragment_shader.glsl"));

    unsigned int shader = create_shader(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shader);

    float fov = 45.0f;
    float aspect = screenWidth/screenHeight;
    float near = 0;
    float far = 200;

    //float* projectionMatrix = new float[16];
    //create_projection_matrix(projectionMatrix, fov, aspect, near, far);

    Matrix projectionMatrix = Matrix::create_projection_matrix(fov, aspect, near, far);

    unsigned int projectionMatrixLocation = glGetUniformLocation(shader, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix.data[0]);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}