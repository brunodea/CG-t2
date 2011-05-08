#include "Game/Player.h"
#include "glfw.h"
#include "Core/matrix_functions.hpp"

#include <iostream>

using namespace Game;

Player::Player()
    : Ship(GameObject::PLAYER)
{
    init();
}

Player::Player(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos)
    : Ship(dir, speed, pos, GameObject::PLAYER)
{
    init();
}

void Player::init()
{
    m_fAcceleration = 0.003f;
    m_fMaxSpeed = .01f;
    Core::Vector3 v(1);
    v[0] = 0.f;
    v[1] = 1.f;
    setDirection(v);

    initVertices();
}

void Player::initVertices()
{
    float width = .1f;
    float height = width;
    Core::Vector3 v1(1);
    v1[0] = -width;
    v1[1] = -height;

    Core::Vector3 v2(1);
    v2[0] = -width;
    v2[1] = height;

    Core::Vector3 v3(1);
    v3[0] = m_vPosition3[0];
    v3[1] = height + 0.06f;

    Core::Vector3 v4(1);
    v4[0] = width;
    v4[1] = height;

    Core::Vector3 v5(1);
    v5[0] = width;
    v5[1] = -height;
    
    std::vector<Core::Vector3> *vec = new std::vector<Core::Vector3>();
    vec->push_back(v1);
    vec->push_back(v2);
    vec->push_back(v3);
    vec->push_back(v4);
    vec->push_back(v5);

    setVertices(*vec);
}


void Player::onRender()
{
    glColor3f(0.f, 0.5f, 0.f);
    glBegin(GL_POLYGON); //quadrado
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

void Player::onCollision(GameObject *obj)
{
}

void Player::onUpdate()
{
    int toRotate = 0;
    float intertia = 0.f;
    if(glfwGetKey(GLFW_KEY_RIGHT))
        toRotate = -1;
    else if(glfwGetKey(GLFW_KEY_LEFT))
        toRotate = 1;
    if(glfwGetKey(GLFW_KEY_UP))
    {
        setSpeed(getSpeed() + getAcceleration());
        if(getSpeed() > getMaxSpeed())
            setSpeed(getMaxSpeed());
    }
    else
        intertia = getSpeed() / 50.f;


    if(toRotate != 0)
    {
        float angle = .03f;

        /*Core::Vector3 v = m_vDirection3;
        if(m_fSpeed != 0)
            v *= m_fSpeed;

        Core::Vector3 v2(1);
        v2[1] = 0.f;

        float ang_2 = Core::angle(v, v2);
        v2 = Core::rotate(toRotate*ang_2)*v2;

        Core::Vector3 v3 = v;
        v3 += v2;

        angle = Core::angle(v, v3); */

        rotate(toRotate*angle);
    }

    if(m_fSpeed > 0.f)
    {
        move();
        setSpeed(getSpeed() - intertia); //inércia?
    }
    else
       m_fSpeed = 0.f;
}

void Player::onKeyEvent(int key, int state)
{
}

