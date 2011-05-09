#include "glfw.h"
#include <cstdlib>

#include "macros.h"
#include "Game/GameController.h"
#include "Game/Shot.hpp"

/*
 * Callback functions
 */
void GLFWCALL keyEventCallback(int key, int state)
{
    GAME.keyEvent(key, state);
}

void GLFWCALL mousePosCallback(int x, int y)
{
    GAME.mousePosEvent(x, y);
}

void GLFWCALL mouseButtonCallback(int button, int action)
{
    GAME.mouseButtonEvent(button, action);
}

void GLFWCALL handleResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setCallBacks()
{
    glfwSetKeyCallback(keyEventCallback);
    glfwSetMousePosCallback(mousePosCallback);
    glfwSetMouseButtonCallback(mouseButtonCallback);

    glfwSetWindowSizeCallback(handleResize);
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

    setCallBacks();

    GAME.run();
    delete GAME_FPS;

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

