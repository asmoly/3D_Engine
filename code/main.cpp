#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "Error loading GLFW!" << std::endl;
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}