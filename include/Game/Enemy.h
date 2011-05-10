#ifndef _BRUNODEA_CG_T2_ENEMY_H_
#define _BRUNODEA_CG_T2_ENEMY_H_

/*
 * Interface Enemy.
 */

#include "glfw.h"
#include "Game/Ship.hpp"

namespace Game
{
    class Enemy : public Ship
    {
    public:
        Enemy() : Ship(GameObject::ENEMY) 
        {
        }
        Enemy(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos) 
            : Ship(dir, speed, pos, GameObject::ENEMY)
        {
        }

        /***********************
         *  Virtual Functions  *
         ***********************/

        virtual void update() { move(); }
        virtual void onCollision(GameObject *obj) = 0;
        
    }; //end of class Enemy.
} //end of namespace Game.

#endif
