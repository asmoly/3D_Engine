#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Matrix.h"
#include "Vector.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"

int main(void)
{
    Mesh mesh("models/helmet.obj");
    //mesh.print();

    const int screenWidth = 1000;
    const int screenHeight = 1000;

    Camera camera;
    Matrix cameraTransform;

    Matrix modelTransform = Matrix::create_transform_matrix(0.0, 45.0, 0.0, 0.0, 0.0, -50.0);
    Matrix projectionMatrix = Matrix::create_projection_matrix(45.0f, screenWidth/screenHeight, 0.1f, 10000.0f);

    float* lights = new float[300];
    int lightsCount = 0;

    lights[0] = 20.0f;
    lights[1] = 20.0f;
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Renderer renderer;
    Shader shader("shaders/vertex_shader.glsl", "shaders/geometry_shader.glsl", "shaders/fragment_shader.glsl");

    VertexBuffer vb(mesh.vertices, sizeof(float)*mesh.vertexCount);
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.push(4); 
    vertexBufferLayout.push(2);

    VertexArray va;
    va.add_buffer(vb, vertexBufferLayout);

    IndexBuffer ib = IndexBuffer(mesh.indices, mesh.indexCount);

    Texture texture("textures/helmet.png");
    texture.load();
    texture.bind();
    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    glEnable(GL_DEPTH_TEST);

    float rotation = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            camera.x += -cosf((camera.yRotation*3.1415)/180.0)*0.08;
            camera.z += sinf((camera.yRotation*3.1415)/180.0)*0.08;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            camera.x -= -cosf((camera.yRotation*3.1415)/180.0)*0.08;
            camera.z -= sinf((camera.yRotation*3.1415)/180.0)*0.08;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            camera.x += -cosf(((camera.yRotation - 90.0)*3.1415)/180.0)*0.08;
            camera.z += sinf(((camera.yRotation - 90.0)*3.1415)/180.0)*0.08;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            camera.x -= -cosf(((camera.yRotation - 90.0)*3.1415)/180.0)*0.08;
            camera.z -= sinf(((camera.yRotation - 90.0)*3.1415)/180.0)*0.08;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            camera.y += 0.08;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            camera.y -= 0.08;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            camera.xRotation += 1.0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            camera.xRotation -= 1.0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            camera.yRotation += 1.0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            camera.yRotation -= 1.0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.clear();

        rotation += 0.5f;
        modelTransform = Matrix::create_transform_matrix(0.0, 0.0, 0.0, 0.0, 0.0, -10.0);
        cameraTransform = camera.get_camera_transformation();

        shader.set_uniform_mat4(projectionMatrix, "projectionMatrix", false);
        shader.set_uniform_mat4(modelTransform, "modelTransform", true);
        shader.set_uniform_mat4(cameraTransform, "cameraTransform", true);
        shader.set_uniform_int(lightsCount, "lightsCount");
        shader.set_uniform_array(lights, 300, "lightSources");
        shader.set_uniform_vec3(camera.x, camera.y, camera.z, "cameraPos");
        shader.set_uniform_int(0, "textureUnit");

        texture.bind();

        renderer.draw(va, ib, shader, mesh.drawType);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}