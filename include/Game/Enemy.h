#ifndef _BRUNODEA_CG_T2_ENEMY_H_
#define _BRUNODEA_CG_T2_ENEMY_H_

#include "glfw.h"
#include "Game/GameObject.hpp"
#include "Core/ShapeRect.h"

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

            initVertices();
            initMultiShape();
            setSpeed(.00003f);
            setDirection(Core::Vector3(1));
        }
        Enemy(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos) 
            : GameObject(dir, speed, pos, GameObject::ENEMY)
        {
            initVertices();
            initMultiShape();
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
        
            //m_MultiShape.onRender(); //comentado ja que nada é desenhado mesmo.
        }

        virtual void onUpdate()
        {
            move();
            m_MultiShape.setRelPos(m_vPosition3);
        }
        virtual void onCollision(GameObject *obj) {/**/};
    private:

        virtual void initVertices()
        {
            float width = .3f;
            float height = width;
            Core::Vector3 v1(1);
            v1[0] = -width;
            v1[1] = -height;

            Core::Vector3 v2(1);
            v2[0] = -width;
            v2[1] = height;

            Core::Vector3 v3(1);
            v3[0] = width;
            v3[1] = height;

            Core::Vector3 v4(1);
            v4[0] = width;
            v4[1] = -height;

            std::vector<Core::Vector3> *vec = new std::vector<Core::Vector3>();
            vec->push_back(v1);
            vec->push_back(v2);
            vec->push_back(v3);
            vec->push_back(v4);

            setVertices(*vec);
        }

        virtual void initMultiShape()
        {
            Core::ShapeRect *rect = new Core::ShapeRect(Core::Vector2(0), .3f, .3f);
            m_MultiShape.addShape(rect);
        }

    }; //end of class Enemy.
} //end of namespace Game.

#endif
