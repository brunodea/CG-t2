#ifndef _BRUNODEA_CG_T2_PLAYER_H_
#define _BRUNODEA_CG_T2_PLAYER_H_

#include "Game/Ship.hpp"

namespace Game
{
    class Player : public Ship
    {
    public:
        Player();
        Player(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos);

        /* fun��o chamada ap�s o update b�sico de Ship. */
        void update();
        void onCollision(GameObject *obj);
        void onKeyEvent(int key, int state);
    private:
        Core::Vector3 m_vShotPos3; //lugar de onde o tiro vai sair.

    private:
        void init();

    }; //end of class Player.
} //end of namespace Player.

#endif
