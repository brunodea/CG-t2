/*
 * Bruno Romero de Azevedo. 2910098
 * Quesitos implementados:
 * Classes em C++ para Vetores, Matrizes e transforma��es geom�tricas.
 * Sistema de controle do ve�culo: Via setas e mouse.
 * Poss�vel dar tiros.
 * Naves inimigas que atiram no jogador.
 */

#include "glfw.h"
#include <cstdlib>

#include "macros.h"
#include "Game/GameController.h"
#include "Game/Shot.hpp"
#include "Game/TextureID.hpp"
#include "FPS.hpp"

GLuint Game::TextureID::m_sTextureID[SIZE];
FPS *FPS::m_sInstance = NULL;

//da um print de ajuda.
void printMenu()
{
    std::cout << "******************************************" << std::endl;
    std::cout << "*   CG - T2 :: Bruno Romero de Azevedo   *" << std::endl;
    std::cout << "******************************************" << std::endl;
    std::cout << "|                 Help                   |" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "1) Para atirar, aperte o left ctrl. " << std::endl;
    std::cout << "2) Segurar barra de espaco para a nave seguir o mouse." << std::endl;
    std::cout << "3) Setas para os lados rotacionam a nave." << std::endl;
    std::cout << "4) Seta para cima acelera. Seta para baixo freia." << std::endl;
}


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
    
    Game::TextureID::initTextures();
    printMenu();
    GAME.initGameObjects();
    setCallBacks();

    GAME.run(); //roda o jogo.

    Game::TextureID::clear();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

