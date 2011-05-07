#include "Game/GameController.h"
#include "glfw.h"

#include "macros.h"

#include <string>
#include <sstream>
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
    double start_time = glfwGetTime();
    double current_time = 0;
    double wait_time = (double)1/60;
    double diff_time = 0;
    int frames = 0;
    while(m_iIsRunning)
    {        
        update();

        current_time = glfwGetTime();
        diff_time = current_time - start_time;
        if(diff_time >= 1 || frames == 0) //1segundo.
        {
            std::stringstream ss;
            ss << "CG - t2. FPS: " << frames;
            glfwSetWindowTitle(ss.str().c_str());
            
            frames = 0;
            start_time = glfwGetTime();
        }
        
        frames++;
        render();

        if(diff_time < wait_time)
            glfwSleep(wait_time - diff_time);
    }
}

void GameController::update()
{
    m_iIsRunning = glfwGetWindowParam(GLFW_OPENED);
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
    //std::cout << x << ',' << y << std::endl;
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
