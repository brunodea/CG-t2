#include "Game/Player.h"
#include "glfw.h"
#include "Core/matrix_functions.hpp"
#include "functions.hpp"
#include "Game/Shot.hpp"
#include "Game/GameController.h"
#include "macros.h"

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

    float w = .71f/5;
    float h = .46f/5;
    initVertices(w, h);
    m_vShotPos3[0] = m_vPosition3[0];
    m_vShotPos3[1] = m_vPosition3[1] + h;
    m_bAccelerate = false;
}

void Player::onCollision(GameObject *obj)
{
}

void Player::update()
{
    //followMouse();

    int toRotate = 0;
    float intertia = 0.f;
    if(glfwGetKey(GLFW_KEY_RIGHT))
        toRotate = -1;
    else if(glfwGetKey(GLFW_KEY_LEFT))
        toRotate = 1;
    if(glfwGetKey(GLFW_KEY_UP))
    {
        m_bAccelerate = true;
    }
    else if(glfwGetKey(GLFW_KEY_DOWN))
    {
        m_bAccelerate = false;
    }

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
        m_vShotPos3 = Core::rotate(toRotate*angle)*m_vShotPos3;
    }

    if(m_bAccelerate)
        accelerate();
    else
        intertia = getSpeed() / 50.f;

    if(m_fSpeed > 0.f)
    {
        move();
        setSpeed(getSpeed() - intertia);
    }
    else
       m_fSpeed = 0.f;
}

void Player::onKeyEvent(int key, int state)
{
    if(key == GLFW_KEY_LCTRL)
    {
        if(state == GLFW_PRESS)
        {
            NormalShot *s = new NormalShot();
            Core::Vector3 v = m_vShotPos3;
            v += m_vPosition3;
            v[2] = 1;
            s->setPos(v);
            s->setDirection(m_vDirection3);
            s->setSpeed(.03f);
            setShotsPerSecond(2);
            if(!shoot(s))
                delete s;
        }
    }
}

void Player::accelerate()
{
    setSpeed(getSpeed() + getAcceleration());
    if(getSpeed() > getMaxSpeed())
        setSpeed(getMaxSpeed());
}

void Player::onMousePosEvent(int x, int y)
{
    m_Mouse.x = x;
    m_Mouse.y = y;

    followMouse();
}

void Player::onMouseButtonEvent(int button, int action)
{
}

void Player::followMouse()
{
    if(m_Mouse.isInsideWindow())
    {
        //m_bAccelerate = true;
        Core::Vector2 v = m_Mouse.toVector2();
        float ang = rotateTo(v);
        m_vShotPos3 = Core::rotate(ang)*m_vShotPos3;
    }
    else
        m_bAccelerate = false;
}