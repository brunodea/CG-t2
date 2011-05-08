#include "glfw.h"
#include <cstdlib>

#include "macros.h"
#include "Game/GameController.h"
#include "Game/Shot.hpp"

void GLFWCALL handleResize(int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    if(!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 8, 8, 8, 8, 8, 8, GLFW_WINDOW))
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    glfwSetWindowSizeCallback(handleResize);

    GAME.run();
    delete GAME_FPS;

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

