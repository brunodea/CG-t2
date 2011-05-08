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
                if(!isAlive())
                    m_fSpeed = 0;
                if(m_vPosition3[0] < 0 || m_vPosition3[0] >= WINDOW_WIDTH || m_vPosition3[1] < 0 || m_vPosition3[1] >= WINDOW_HEIGHT)
                    setLifes(0);
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
            m_iImage = loadTexture("resources/shot_laser.tga");
            initVertices(.04f/5, .39f/5);
        }
    }; //end of struct NormalShot.

} //end of namespace Game.

#endif
