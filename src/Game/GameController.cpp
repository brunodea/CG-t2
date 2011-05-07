#include "Game/GameController.h"
#include "glfw.h"

using namespace Game;

GameController *GameController::m_sInstance = NULL;

GameController::GameController()
    : m_iIsRunning(GL_TRUE)
{
    //glfwSetKeyCallback(keyEvent);
}

GameController::~GameController()
{
    glfwSetKeyCallback(NULL);
}

GameController &GameController::instance()
{
    if(m_sInstance == NULL)
        m_sInstance = new GameController();
    return *m_sInstance;
}

void GameController::run()
{
    while(m_iIsRunning)
    {
        render();
        keyEvent(0,0);
    }
}

void GameController::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers();
}

void GLFWCALL GameController::keyEvent(int key, int key_state)
{
    //if(key == GLFW_KEY_ESC)
    //    m_iIsRunning = GL_FALSE;
    m_iIsRunning = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}
