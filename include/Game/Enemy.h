#ifndef _BRUNODEA_CG_T2_ENEMY_H_
#define _BRUNODEA_CG_T2_ENEMY_H_

#include "glfw.h"
#include "Game/Ship.hpp"

#include <iostream>

namespace Game
{
    class Enemy : public Ship
    {
    public:
        Enemy() : Ship(GameObject::ENEMY) 
        {
            /*Core::Vector3 pos;
            pos[0] = 0.f;
            pos[1] = 0.f;
            setPos(pos);

            initVertices();
            initMultiShape();
            setSpeed(.00002f);
            Core::Vector3 dir(1);
            dir[0] = 1;
            dir[1] = 1;
            setDirection(dir);*/
        }
        Enemy(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos) 
            : Ship(dir, speed, pos, GameObject::ENEMY)
        {
            /*initVertices();
            initMultiShape();*/
        }

        /***********************
         *  Virtual Functions  *
         ***********************/

        virtual void onRender()
        {
            glColor3f(0.f, 0.5f, 0.f);
            glBegin(GL_QUADS); //quadrado
                for(unsigned int i = 0; i < m_vVertices.size(); i++)
                {
                    Core::Vector3 vec(1);
                    vec[0] = (m_vVertices.at(i)+m_vPosition3)(0,0);
                    vec[1] = (m_vVertices.at(i)+m_vPosition3)(1,0);
                    glVertex2f(vec[0], vec[1]);
                }
            glEnd();
        
            //m_MultiShape.onRender();
        }

        virtual void onUpdate() { move(); }
        virtual void onCollision(GameObject *obj) = 0;
        
    }; //end of class Enemy.
} //end of namespace Game.

#endif
