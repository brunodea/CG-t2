#include "Game/GameController.h"
#include "glfw.h"

using namespace Game;

GameController::GameController()
    : m_iIsRunning(GL_TRUE)
{
}

void GameController::run()
{
    while(m_iIsRunning)
    {
        render();
        keyEvent();
    }
}

void GameController::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers();
}

void GameController::keyEvent()
{
    m_iIsRunning = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}
