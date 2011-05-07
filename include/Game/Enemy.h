#ifndef _BRUNODEA_CG_T2_ENEMY_H_
#define _BRUNODEA_CG_T2_ENEMY_H_

#include "Game/GameObject.hpp"
#include "glfw.h"

#include <iostream>

namespace Game
{
    class Enemy : public GameObject
    {
    public:
        Enemy() : GameObject(GameObject::ENEMY) 
        {
            Core::Vector3 pos;
            pos[0] = 0.f;
            pos[1] = 0.f;
            setPos(pos);
        }
        Enemy(const Core::Vector3 &dir, const Core::Vector3 &speed, const Core::Vector3 &pos) 
            : GameObject(dir, speed, pos, GameObject::ENEMY)
        {/**/}

        /***********************
         *  Virtual Functions  *
         ***********************/

        virtual void onRender()
        {
            float offset = .3f;
            glColor3f(0.f, 0.5f, 0.f);
            glBegin(GL_QUADS); //quadrado
                glVertex2f(getPos()[0] - offset, getPos()[1] - offset);
                glVertex2f(getPos()[0] - offset, getPos()[1] + offset);
                glVertex2f(getPos()[0] + offset, getPos()[1] - offset);
                glVertex2f(getPos()[0] + offset, getPos()[1] + offset);
            glEnd();
        }

        virtual void onUpdate() {/**/}
        virtual void onCollision(GameObject *obj) {/**/};

    }; //end of class Enemy.
} //end of namespace Game.

#endif
