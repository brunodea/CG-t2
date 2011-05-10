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
    m_pPlayer = new Player();
    Core::Vector3 pos(1);
    pos[0] = WINDOW_WIDTH/2.f;
    pos[1] = WINDOW_HEIGHT - 40;
    m_pPlayer->setPos(pos);
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
    double frame_inter = 1.f/60.f;
    double update_inter = 1.f/90.f;
    double diff_time = 0;
    double last_time = 0;
    int frames = 0;
    while(m_iIsRunning)
    {        
        current_time = glfwGetTime();
        diff_time = current_time - start_time;
        if(diff_time >= 1 || frames == 0) //1segundo.
        {
            std::stringstream ss;
            ss << "CG - t2. FPS: " << frames;
            glfwSetWindowTitle(ss.str().c_str());
            
            frames = 0;
        }
        
        if(diff_time > update_inter)
            update();

        if(diff_time > frame_inter)
        {
            render();
            start_time = glfwGetTime();
        }
        
        frames++;
        glfwSleep(update_inter - (current_time + glfwGetTime()));
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
    if(x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
        return;
    m_pPlayer->onMousePosEvent(x, y);
}

void GameController::mouseButtonEvent(int button, int action)
{
    m_pPlayer->onMouseButtonEvent(button, action);
}
