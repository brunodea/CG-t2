#ifndef _BRUNODEA_CG_T2_SHOT_HPP_
#define _BRUNODEA_CG_T2_SHOT_HPP_

#include "Game/GameObject.hpp"
#include "Core/MultiShape.h"
#include "Core/matrix_functions.hpp"

namespace Game
{
    class Shot : public GameObject
    {
    public:
        Shot(unsigned int damage) : GameObject(GameObject::SHOT), m_iDamage(damage) {}

        virtual void onRender() = 0;
        virtual void onUpdate() 
        {
        }
        virtual void onCollision(GameObject *obj) {/**/}
        
    private:
        unsigned int m_iDamage;

    }; //end of class Shot.
} //end of namespace Game.

#endif
