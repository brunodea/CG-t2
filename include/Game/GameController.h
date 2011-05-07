#ifndef _BRUNODEA_CG_T2_GAME_H_
#define _BRUNODEA_CG_T2_GAME_H_


namespace Game
{
    class GameController
    {
    public:
        GameController();

        void run();
    private:
        int m_iIsRunning;

    private:
        void render();
        void keyEvent();
    }; //end of class GameController.

} //end of namespace Game.

#endif
