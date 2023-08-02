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
    const int screenHeight = 1000;

    Mesh mesh;
    mesh.load_from_obj("models/monkey.obj");

    Matrix modelTransform = Matrix::create_transform_matrix(0.0, 45.0, 0.0, 0.0, 0.0, -50.0);
    Matrix projectionMatrix = Matrix::create_projection_matrix(45.0f, screenWidth/screenHeight, 0.1f, 10000.0f);

    float* lights = new float[300];
    int lightsCount = 0;

    lights[0] = 30.0f;
    lights[1] = -30.0f;
    lights[2] = 0.0f;
    lightsCount ++;

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
                         0.5f,  0.5f, -2.0f, 1.0f,
                         0.5f, -0.5f, -2.0f,  1.0f};

    unsigned int indexCount = 6; 
    unsigned int indices[] = {0, 1, 2,
                              2, 3, 0};

    Renderer renderer;

    // Shader
    Shader shader("shaders/vertex_shader.glsl", "shaders/geometry_shader.glsl", "shaders/fragment_shader.glsl");

    // Buffers
    
    VertexArray va;

    VertexBuffer vb(mesh.vertices, sizeof(float)*mesh.vertexCount);
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.push(4);
    va.add_buffer(vb, vertexBufferLayout);

    IndexBuffer ib(mesh.indices, mesh.indexCount);

    va.unbind();
    shader.unbind();
    vb.unbind();
    ib.unbind();

    glEnable(GL_DEPTH_TEST);

    float rotation = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.clear();

        rotation += 0.5f;
        modelTransform = Matrix::create_transform_matrix(0.0, rotation, 0.0, 0.0, 0.0, -10.0);

        shader.set_uniform_mat4(projectionMatrix, "projectionMatrix", false);
        shader.set_uniform_mat4(modelTransform, "modelTransform", true);
        shader.set_uniform_int(lightsCount, "lightsCount");
        shader.set_uniform_array(lights, 300, "lightSources");

        renderer.draw(va, ib, shader, mesh.drawType);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}