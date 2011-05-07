#ifndef _BRUNODEA_CG_T2_SHOT_HPP_
#define _BRUNODEA_CG_T2_SHOT_HPP_

#include "Game/GameObject.hpp"
#include "Core/MultiShape.h"
#include "Core/ShapeRect.h"
#include "Core/matrix_functions.hpp"

namespace Game
{
    class Shot : public GameObject
    {
    public:
        Shot(unsigned int damage) : GameObject(GameObject::SHOT), m_iDamage(damage) 
        {
            initShapes();
        }

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
    protected:
        virtual void initShapes()
        {
            Core::ShapeRect *shape = new Core::ShapeRect(Core::Vector2(0), .03f, .03f);
            m_MultiShape.addShape(shape);
        }

    private:
        unsigned int m_iDamage;

        Core::MultiShape m_MultiShape;

    }; //end of class Shot.
} //end of namespace Game.

#endif
