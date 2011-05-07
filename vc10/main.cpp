#include "glfw.h"
#include <cstdlib>

#include "macros.h"
#include "Game/GameController.h"

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

    Game::GameController game;
    game.run();

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

