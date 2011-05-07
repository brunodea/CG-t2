#ifndef _BRUNODEA_CG_T2_GAME_H_
#define _BRUNODEA_CG_T2_GAME_H_


namespace Game
{
    class GameController
    {
    public:
        GameController();

        int run();
    private:
        int isRunning;

    private:
        void render();
    }; //end of class GameController.

} //end of namespace Game.

#endif
