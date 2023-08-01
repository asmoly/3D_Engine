#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Matrix.h"
#include "Vector.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    Matrix projectionMatrix = Matrix::create_projection_matrix(45.0f, screenWidth/screenHeight, 0.1f, 200.0f);

    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "Error loading GLFW!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    unsigned int vertexCount = 4;
    float vertices[] = {-0.5f, -0.5f, -2.0f,  1.0f,
                        -0.5f,  0.5f, -2.0f,  1.0f,
                         0.5f,  0.5f, -10.0f, 1.0f,
                         0.5f, -0.5f, -2.0f,  1.0f};

    unsigned int indexCount = 6; 
    unsigned int indices[] = {0, 1, 2,
                              2, 3, 0};

    Renderer renderer;

    // Shader
    Shader shader("shaders/vertex_shader.glsl", "shaders/geometry_shader.glsl", "shaders/fragment_shader.glsl");

    // Buffers
    
    VertexArray va;

    VertexBuffer vb(vertices, sizeof(float)*4*vertexCount);
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.push(4);
    va.add_buffer(vb, vertexBufferLayout);

    IndexBuffer ib(indices, indexCount);

    va.unbind();
    shader.unbind();
    vb.unbind();
    ib.unbind();

    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();

        // Binding shader
        shader.set_unfirom_mat4(projectionMatrix, "projectionMatrix");

        renderer.draw(va, ib, shader);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}