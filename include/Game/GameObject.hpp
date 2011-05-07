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
        GameObject(Type type) : m_Type(type) {}

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

    private:
        Type m_Type;
        Core::Vector3 m_vDirection3;
        Core::Vector3 m_vSpeed3;
        Core::Vector3 m_vPosition3;

    }; //end of class GameObject.
} //end of namespace Game.

#endif
