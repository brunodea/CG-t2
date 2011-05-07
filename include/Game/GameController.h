#ifndef _BRUNODEA_CG_T2_GAME_H_
#define _BRUNODEA_CG_T2_GAME_H_

#include "Game/Enemy.h"
#include "Game/Player.h"

namespace Game
{
    class GameController
    {
    public:
        ~GameController();
        static GameController &instance();

        void run();

    private:
        static GameController *m_sInstance;

        int m_iIsRunning;

    private:
        GameController();

        void render();
        void update();

        void mousePosEvent(int x, int y);
        void keyEvent(int key, int state);

        static void keyEventCallback(int key, int state);
        static void mousePosCallback(int x, int y);

        Enemy *m_pTestEnemy;
        Player *m_pPlayer;

    }; //end of class GameController.

} //end of namespace Game.

#endif
