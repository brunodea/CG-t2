#include "Game/GameController.h"
#include "glfw.h"

#include <iostream>

using namespace Game;

GameController *GameController::m_sInstance = NULL;

GameController::GameController()
    : m_iIsRunning(GL_TRUE)
{
    glfwSetKeyCallback(keyEventCallback);
    glfwSetMousePosCallback(mousePosCallback);
}

GameController::~GameController()
{
    glfwSetKeyCallback(NULL);
}

GameController &GameController::instance()
{
    if(m_sInstance == NULL)
    {
        m_sInstance = new GameController();
    }
    return *m_sInstance;
}

void GameController::run()
{
    while(m_iIsRunning)
    {
        render();
        
        m_iIsRunning = glfwGetWindowParam(GLFW_OPENED);
    }
}

void GameController::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers();
}

void GameController::keyEvent(int key, int state)
{
    if(key == GLFW_KEY_ESC)
        m_iIsRunning = GL_FALSE;
}

void GameController::mousePosEvent(int x, int y)
{
    std::cout << x << ',' << y << std::endl;
}

/*
 * Callback functions
 */
void GLFWCALL GameController::keyEventCallback(int key, int state)
{
    m_sInstance->keyEvent(key, state);
}

void GLFWCALL GameController::mousePosCallback(int x, int y)
{
    m_sInstance->mousePosEvent(x, y);
}
