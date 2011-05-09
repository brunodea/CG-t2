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

        /* função chamada após o update básico de Ship. */
        void update();
        void onCollision(GameObject *obj);
        void onKeyEvent(int key, int state);
        void onMousePosEvent(int x, int y);
        void onMouseButtonEvent(int button, int action);
    private:
        Core::Vector3 m_vShotPos3; //lugar de onde o tiro vai sair.
        bool m_bAccelerate;

    private:
        void init();
        void followMouse();
    }; //end of class Player.
} //end of namespace Player.

#endif
