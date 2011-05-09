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
        void mouseButtonEvent(int button, int action);
        void keyEvent(int key, int state);

        static void keyEventCallback(int key, int state);
        static void mousePosCallback(int x, int y);
        static void mouseButtonCallback(int button, int action);

        Player *m_pPlayer;
        Mouse m_Mouse;

    }; //end of class GameController.

} //end of namespace Game.

#endif
