#ifndef _BRUNODEA_CG_T2_GAME_H_
#define _BRUNODEA_CG_T2_GAME_H_

/* 
 * Classe que controla o game como um todo.
 * Singleton.
 */

#include "Game/GameObject.hpp"
#include "Game/Player.h"
#include "Game/NormalEnemy.h"

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

        inline Player *getPlayer() { return m_pPlayer; }

        /* Callbacks. */
        void mousePosEvent(int x, int y);
        void mouseButtonEvent(int button, int action);
        void keyEvent(int key, int state);

    private:
        static GameController *m_sInstance;

        int m_iIsRunning;

        Player *m_pPlayer;
        std::vector<NormalEnemy *> m_vNormalEnemies;

    private:
        GameController();

        void render();
        void update();
        void initPlayer();
        void initEnemies();
    }; //end of class GameController.

} //end of namespace Game.

#endif
