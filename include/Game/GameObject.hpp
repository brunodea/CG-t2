#ifndef _BRUNODEA_CG_T2_GAME_OBJECT_HPP_
#define _BRUNODEA_CG_T2_GAME_OBJECT_HPP_

#include "Core/matrix_functions.hpp"

namespace Game
{
    class GameObject
    {
    public:
        enum Type
        {
            ENEMY,
            PLAYER,
            OBJECT
        }; //end of enum Type.

    public:
        GameObject()
        {
            m_Type = OBJECT;
            init();
        }

        GameObject(Type type) : m_Type(type) 
        {
            init();
        }

        GameObject(const Core::Vector3 &dir, const Core::Vector3 &speed, const Core::Vector3 &pos, Type type)
            : m_vDirection3(dir), m_vSpeed3(speed), m_vPosition3(pos), m_Type(type)
        {
            m_iLifes = 1;
        }


        /***********************
         *  Virtual Functions  *
         ***********************/

        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onCollision(GameObject *obj) = 0;
        virtual void onKeyEvent(int key, int state) {/**/}


        /*************************
         *  Setters & Getters    *
         *************************/

        inline void setDirection(const Core::Vector3 &dir) { m_vDirection3 = dir; }
        inline Core::Vector3 &getDirection() { return m_vDirection3; }
        
        inline void setSpeed(const Core::Vector3 &speed) { m_vSpeed3 = speed; }
        inline Core::Vector3 &getSpeed() { return m_vSpeed3; } 

        inline void setPos(const Core::Vector3 &pos) { m_vPosition3 = pos; }
        inline Core::Vector3 &getPos() { return m_vPosition3; }

        inline void setLifes(unsigned int lifes) { m_iLifes = lifes; }

    private:
        Core::Vector3 m_vDirection3;
        Core::Vector3 m_vSpeed3;
        Core::Vector3 m_vPosition3;

        Type m_Type;

        unsigned int m_iLifes;

    private:
        inline void init()
        {
            Core::Vector3 v_init;
            v_init.clear(0.f);

            setDirection(v_init);
            setSpeed(v_init);
            setPos(v_init);

            m_iLifes = 1;
        }

    }; //end of class GameObject.
} //end of namespace Game.

#endif
