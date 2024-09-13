#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Pong.h"
#include "Renderer.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //Using OpenGL 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 1024, "PONG", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        std::cout << "Error" << std::endl;
    Pong pong;

    std::cout << "Enter the Name of the First Player\n";
    std::string a;
    std::cin >> a;
    pong.p1 = a;

    std::cout << "Enter the Name of the Second Player\n";
    std::cin >> a;
    pong.p2 = a;


    float lastTime = (float)glfwGetTime();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        pong.ProcessInput(deltaTime);

        if (!pong.m_GameOver)
        {
            pong.Update(deltaTime);
            pong.Render();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}