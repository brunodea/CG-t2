#include "glfw.h"
#include <cstdlib>

#include "macros.h"

int main()
{
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    if(!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    int running = GL_TRUE;
    while(running)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers();

        running = !glfwGetKey(GLFW_KEY_ESC);
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

