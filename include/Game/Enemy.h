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
        enum Type
        {
            NORMAL_ENEMY = 0x00000001
        }; //end of enum Type.
    public:
        Enemy(Type type) : Ship(GameObject::ENEMY) 
        {
            m_iType = m_iType | type;
            m_pVictim = NULL;
        }
        Enemy(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos, Type type) 
            : Ship(dir, speed, pos, GameObject::ENEMY)
        {
            m_iType = m_iType | type;
            m_pVictim = NULL;
        }

        void setVictim(GameObject *go) { m_pVictim = go; }

        /***********************
         *  Virtual Functions  *
         ***********************/

        virtual void update() { move(); }
        virtual void onCollision(GameObject *obj) = 0;
        
    protected:
        GameObject *m_pVictim;
    }; //end of class Enemy.
} //end of namespace Game.

#endif
