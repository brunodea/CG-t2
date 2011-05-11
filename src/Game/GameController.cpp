#include "Game/GameController.h"
#include "Game/Player.h"
#include "glfw.h"
#include "FPS.hpp"

#include "macros.h"
#include "Game/NormalEnemy.h"

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
    for(unsigned int i = 0; i < m_vNormalEnemies.size(); i++)
        delete m_vNormalEnemies.at(i);
    m_vNormalEnemies.clear();
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
    /* Ajustes do FPS. */
    double next_game_tick = glfwGetTime();
    int loops = 0;
    double current_time = 0;
    double diff_time = 0;
    double last_time = 0;

    double init_fps_time = 0;
    while(m_iIsRunning)
    {
        loops = 0;
        while(glfwGetTime() > next_game_tick && loops < MAX_FRAMESKIP)
        {
            update();
            next_game_tick += SKIP_TICKS;
            loops++;
        }
        FPS::instance().setInterpolation(float(glfwGetTime() + SKIP_TICKS - next_game_tick)/float(SKIP_TICKS));
        render();
        //current_time = glfwGetTime();
        //diff_time = current_time - start_time;

        //if(diff_time > update_inter)
        //    update();

        //if(diff_time > frame_inter)
        //{
        //    render();
        //    start_time = glfwGetTime();
        //}
        //glfwSleep(update_inter - (current_time + glfwGetTime()));

        ///* Ajusta o FPS no titulo da janela. */
        //if(glfwGetTime() - init_fps_time >= 1)
        //{
        //    std::stringstream ss;
        //    ss << "CG - t2. FPS: " << frames;
        //    glfwSetWindowTitle(ss.str().c_str());
        //    
        //    init_fps_time = glfwGetTime();   
        //    frames = 0;
        //}
        //frames++;
    }
}

void GameController::update()
{
    m_iIsRunning = glfwGetWindowParam(GLFW_OPENED);

    for(unsigned int i = 0; i < m_vNormalEnemies.size(); i++)
        m_vNormalEnemies.at(i)->onUpdate();
    m_pPlayer->onUpdate();
}

void GameController::render()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    for(unsigned int i = 0; i < m_vNormalEnemies.size(); i++)
        m_vNormalEnemies.at(i)->render();
    m_pPlayer->render();

    glfwSwapBuffers();
}

void GameController::initGameObjects()
{
    std::vector<NormalEnemy *> *m_vNormalEnemies = new std::vector<NormalEnemy *>();
    initPlayer();
    initEnemies();
}

void GameController::initEnemies()
{
    NormalEnemy *normal_enemy = new NormalEnemy();
    Core::Vector3 pos(1);
    pos[0] = WINDOW_WIDTH/2.f;
    pos[1] = 30;
    normal_enemy->setPos(pos);
    normal_enemy->setVictim(m_pPlayer);
    m_vNormalEnemies.push_back(normal_enemy);
}

void GameController::initPlayer()
{
    m_pPlayer = new Player();
    Core::Vector3 pos(1);
    pos[0] = WINDOW_WIDTH/2.f;
    pos[1] = WINDOW_HEIGHT - 40;
    m_pPlayer->setPos(pos);
}

void GameController::keyEvent(int key, int state)
{
    if(key == GLFW_KEY_ESC)
        m_iIsRunning = GL_FALSE;

    for(unsigned int i = 0; i < m_vNormalEnemies.size(); i++)
        m_vNormalEnemies.at(i)->onKeyEvent(key, state);
    m_pPlayer->onKeyEvent(key, state);
}

void GameController::mousePosEvent(int x, int y)
{
    if(x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
        return;
    for(unsigned int i = 0; i < m_vNormalEnemies.size(); i++)
        m_vNormalEnemies.at(i)->onMousePosEvent(x, y);
    m_pPlayer->onMousePosEvent(x, y);
}

void GameController::mouseButtonEvent(int button, int action)
{
    for(unsigned int i = 0; i < m_vNormalEnemies.size(); i++)
        m_vNormalEnemies.at(i)->onMouseButtonEvent(button, action);
    m_pPlayer->onMouseButtonEvent(button, action);
}
