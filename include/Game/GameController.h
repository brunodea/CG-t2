#ifndef _BRUNODEA_CG_T2_GAME_H_
#define _BRUNODEA_CG_T2_GAME_H_

/* 
 * Classe que controla o game como um todo.
 * Singleton.
 */

#include "Game/GameObject.hpp"

#include <vector>

namespace Game
{
    class GameController
    {
    public:
        ~GameController();
        static GameController &instance();
        void run();
        void initGameObjects();

        /* Callbacks. */
        void mousePosEvent(int x, int y);
        void mouseButtonEvent(int button, int action);
        void keyEvent(int key, int state);

    private:
        static GameController *m_sInstance;

        int m_iIsRunning;
        Mouse m_Mouse;

        std::vector<GameObject *> *m_vpGameObjects;

    private:
        GameController();

        void render();
        void update();
        void initPlayer();
    }; //end of class GameController.

} //end of namespace Game.

#endif
