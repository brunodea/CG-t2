#ifndef _BRUNODEA_CG_T2_SHOT_HPP_
#define _BRUNODEA_CG_T2_SHOT_HPP_

#include "Game/GameObject.hpp"
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
            if(!isAlive())
                m_fSpeed = 0;
        }
        virtual void onCollision(GameObject *obj) 
        {
            if(isAlive())
            {
                obj->setLifes(obj->getLifes() - m_iDamage);
                setLifes(0);
            }
        }
    private:
        unsigned int m_iDamage;

    }; //end of class Shot.
} //end of namespace Game.

#endif
