#ifndef _BRUNODEA_CG_T2_SHIP_HPP_
#define _BRUNODEA_CG_T2_SHIP_HPP_

#include "Game/GameObject.hpp"
#include "Game/Shot.hpp"
#include "Core/matrix_functions.hpp"

namespace Game
{
    class Ship : public GameObject
    {
    public:
        Ship(Type type) : GameObject(GameObject::SHIP | type), m_Shot(0), m_fAcceleration(0) 
        {
        }
        Ship(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos, Type type) 
            : GameObject(dir, speed, pos, GameObject::SHIP & type), m_Shot(0), m_fAcceleration(0)
        {
        }

        ~Ship()
        {
            delete m_Shot;
        }

        /*************************/
        /*  Virtual Functions    */
        /*************************/
        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onCollision(GameObject *obj) = 0;
        virtual void onKeyEvent(int key, int state) {/**/}

        /* Setters & Getters */
        inline float getAcceleration() { return m_fAcceleration; }
        inline void setAcceleration(float acc) { m_fAcceleration = acc; }

        inline float getMaxSpeed() { return m_fMaxSpeed; }
        inline void setMaxSpeed(float max) { m_fMaxSpeed = max; }

    protected:
        Shot *m_Shot;
        float m_fAcceleration;
        float m_fMaxSpeed;

    }; //end of class Ship.

} //end of namespace Game.

#endif
