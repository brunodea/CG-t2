#include "glfw.h"
#include <cstdlib>

#include "macros.h"
#include "Game/GameController.h"
#include "Game/Shot.hpp"

void GLFWCALL handleResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Displacement trick for exact pixelization
    //glTranslatef(0.375, 0.375, 0);
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
    handleResize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    glfwSetWindowSizeCallback(handleResize);

    GAME.run();
    delete GAME_FPS;

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

