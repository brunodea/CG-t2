#ifndef _BRUNODEA_CG_T2_SHOT_HPP_
#define _BRUNODEA_CG_T2_SHOT_HPP_

#include "Game/GameObject.hpp"
#include "Core/matrix_functions.hpp"
#include "macros.h"
#include "functions.hpp"

namespace Game
{
    class Shot : public GameObject
    {
    public:
        enum Type
        {
            NORMAL = 0
        }; //end of enum Type.

    public:
        Shot(unsigned int damage, Type type) : GameObject(GameObject::SHOT | type), m_iDamage(damage) 
        {
            setVisible(false);
        }

        virtual void onUpdate() 
        {
            if(isVisible())
            {
                float f = 1.f;
                if(m_vPosition3[0] < -f || m_vPosition3[0] >= f ||
                   m_vPosition3[1] < -f || m_vPosition3[1] >= f)
                    setLifes(0);
                move();
            }
        }
        virtual void onCollision(GameObject *obj) 
        {
            if(isVisible() && isAlive())
            {
                obj->setLifes(obj->getLifes() - m_iDamage);
                setLifes(0);
            }
        }

    private:
        unsigned int m_iDamage;
    }; //end of class Shot.

    struct NormalShot : public Shot
    {
        NormalShot() : Shot(1, Shot::NORMAL) 
        { 
            m_iImage = loadTexture("resources/shot_ball.tga");

            initVertices(.13f/5, .11f/5);
        }

    }; //end of struct NormalShot.
} //end of namespace Game.

#endif
