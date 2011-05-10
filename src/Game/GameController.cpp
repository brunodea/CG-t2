#include "Game/GameController.h"
#include "Game/Player.h"
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
}

GameController::~GameController()
{
    glfwSetKeyCallback(NULL);
    for(unsigned int i = 0; i < m_vpGameObjects->size(); i++)
        delete m_vpGameObjects->at(i);
    m_vpGameObjects->clear();
    delete m_vpGameObjects;
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
    initPlayer();
    /* Ajustes do FPS. */
    double start_time = glfwGetTime();
    double current_time = 0;
    double frame_inter = 1.f/60.f;
    double update_inter = 1.f/90.f;
    double diff_time = 0;
    double last_time = 0;
    int frames = 0;

    double init_fps_time = 0;
    while(m_iIsRunning)
    {        
        current_time = glfwGetTime();
        diff_time = current_time - start_time;

        if(diff_time > update_inter)
            update();

        if(diff_time > frame_inter)
        {
            render();
            start_time = glfwGetTime();
        }
        glfwSleep(update_inter - (current_time + glfwGetTime()));

        /* Ajusta o FPS no titulo da janela. */
        if(glfwGetTime() - init_fps_time >= 1)
        {
            std::stringstream ss;
            ss << "CG - t2. FPS: " << frames;
            glfwSetWindowTitle(ss.str().c_str());
            
            init_fps_time = glfwGetTime();   
            frames = 0;
        }
        frames++;
    }
}

void GameController::update()
{
    m_iIsRunning = glfwGetWindowParam(GLFW_OPENED);

    for(unsigned int i = 0; i < m_vpGameObjects->size(); i++)
        m_vpGameObjects->at(i)->onUpdate();
}

void GameController::render()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    for(unsigned int i = 0; i < m_vpGameObjects->size(); i++)
        m_vpGameObjects->at(i)->render();

    glfwSwapBuffers();
}

void GameController::initGameObjects()
{
    std::vector<GameObject *> *m_vpGameObjects = new std::vector<GameObject *>();
    initPlayer();
}

void GameController::initPlayer()
{
    GameObject *player = new Player();
    Core::Vector3 pos(1);
    pos[0] = WINDOW_WIDTH/2.f;
    pos[1] = WINDOW_HEIGHT - 40;
    player->setPos(pos);

    m_vpGameObjects->push_back(player);
}

void GameController::keyEvent(int key, int state)
{
    if(key == GLFW_KEY_ESC)
        m_iIsRunning = GL_FALSE;

    for(unsigned int i = 0; i < m_vpGameObjects->size(); i++)
        m_vpGameObjects->at(i)->onKeyEvent(key, state);
}

void GameController::mousePosEvent(int x, int y)
{
    if(x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
        return;
    for(unsigned int i = 0; i < m_vpGameObjects->size(); i++)
        m_vpGameObjects->at(i)->onMousePosEvent(x, y);
}

void GameController::mouseButtonEvent(int button, int action)
{
    for(unsigned int i = 0; i < m_vpGameObjects->size(); i++)
        m_vpGameObjects->at(i)->onMouseButtonEvent(button, action);
}
