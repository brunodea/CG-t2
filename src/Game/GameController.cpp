#include "Game/GameController.h"
#include "glfw.h"

using namespace Game;

GameController::GameController()
    : isRunning(GL_TRUE)
{
}

int GameController::run()
{
    while(isRunning)
    {
        render();
    }

    return 0; //tudo certo.
}

void GameController::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers();
}

