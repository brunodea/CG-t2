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

        void onRender();
        void onUpdate();
        void onCollision(GameObject *obj);
        void onKeyEvent(int key, int state);

    private:
        void initMultiShape();
        void initVertices();
        void init();

    }; //end of class Player.
} //end of namespace Player.

#endif
