#ifndef _BRUNODEA_CG_T2_ENEMY_H_
#define _BRUNODEA_CG_T2_ENEMY_H_

#include "Game/GameObject.hpp"

namespace Game
{
    class Enemy : public GameObject
    {
    public:
        Enemy() : GameObject(GameObject::ENEMY) {/**/}
        Enemy(const Core::Vector3 &dir, const Core::Vector3 &speed, const Core::Vector3 &pos) 
            : GameObject(dir, speed, pos, GameObject::ENEMY)
        {/**/}


    }; //end of class Enemy.
} //end of namespace Game.

#endif
