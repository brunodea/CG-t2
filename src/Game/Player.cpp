#include "Game/Player.h"
#include "glfw.h"
#include "Core/matrix_functions.hpp"
#include "functions.hpp"
#include "Game/Shot.hpp"

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
    setVisible(true);
    m_fAcceleration = 0.003f;
    m_fMaxSpeed = .01f;
    Core::Vector3 v(1);
    v[0] = 0.f;
    v[1] = 1.f;
    setDirection(v);

    m_iImage = loadTexture("resources/aircraft.tga");

    initVertices(.71f/5, .46f/5);
}

void Player::onCollision(GameObject *obj)
{
}

void Player::update()
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
    if(key == GLFW_KEY_SPACE)
    {
        if(state == GLFW_PRESS)
        {
            NormalShot *s = new NormalShot();
            Core::Vector3 v = m_vPosition3;
            v[1] += .46f/5;
            s->setPos(v);
            s->setDirection(m_vDirection3);
            s->setSpeed(.03f);
            //s.adjustVerticesAngle();
            if(!shoot(*s))
                delete s;
        }
    }
}

