#ifndef _BRUNODEA_CG_T2_GAME_H_
#define _BRUNODEA_CG_T2_GAME_H_

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
        void mousePosEvent(int x, int y);
        void keyEvent(int key, int state);

        static void keyEventCallback(int key, int state);
        static void mousePosCallback(int x, int y);
    }; //end of class GameController.

} //end of namespace Game.

#endif
