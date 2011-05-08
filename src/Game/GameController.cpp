#include "Game/GameController.h"
#include "glfw.h"

#include "FPS.h"
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

    m_pPlayer = new Player();
}

GameController::~GameController()
{
    glfwSetKeyCallback(NULL);
    delete m_pPlayer;
}

GameController &GameController::instance()
{
    if(m_sInstance == NULL)
    {
        m_sInstance = new GameController();
    }
    return *m_sInstance;
}


//Game Loop.
void GameController::run()
{
    double start_time = glfwGetTime();
    double current_time = 0;
    double interpolation = 0;
    double diff_time = 0;
    int frames = 0;
    while(m_iIsRunning)
    {
        update();
        /*
        frames = 0;
        current_time = glfwGetTime();
        while(current_time > start_time && frames < MAX_FRAMESKIP)
        {
            update();

            start_time += SKIP_TICKS;
            frames++;
        }

        interpolation = float(glfwGetTime() + SKIP_TICKS - start_time)/float(SKIP_TICKS);
        GAME_FPS->setFPS(interpolation);
        */

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
            
        GAME_FPS->setFPS(diff_time);
        
        frames++;
        render();

        //if(diff_time < wait_time)
        //    glfwSleep(wait_time - diff_time);
    }
}

void GameController::update()
{
    m_iIsRunning = glfwGetWindowParam(GLFW_OPENED);
    m_pPlayer->onUpdate();
}

void GameController::render()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    m_pPlayer->render();

    glFlush();
    glfwSwapBuffers();
}

void GameController::keyEvent(int key, int state)
{
    if(key == GLFW_KEY_ESC)
        m_iIsRunning = GL_FALSE;
    m_pPlayer->onKeyEvent(key, state);
}

void GameController::mousePosEvent(int x, int y)
{
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
