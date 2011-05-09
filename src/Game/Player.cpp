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
    m_fAcceleration = .3;
    m_fMaxSpeed = 5;
    Core::Vector3 v(1);
    v[0] = 0.f;
    v[1] = -1.f;
    setDirection(v);

    m_iImage = loadTexture("resources/player_ship.tga");

    float w = 71/3;
    float h = 46/3;
    initVertices(w, h);
    m_vShotPos3[0] = m_vPosition3[0];
    m_vShotPos3[1] = m_vPosition3[1] - h;
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
        toRotate = 1;
    else if(glfwGetKey(GLFW_KEY_LEFT))
        toRotate = -1;
    if(glfwGetKey(GLFW_KEY_UP))
    {
        m_bAccelerate = true;
    }
    else if(glfwGetKey(GLFW_KEY_DOWN)) //para diminuir a velocidade da nave.
    {
        setSpeed(getSpeed()-getAcceleration());
        if(getSpeed() < 0)
            setSpeed(0);
        m_bAccelerate = false;
    }
    else if(glfwGetKey('S')) //para parar a nave.
    {
        intertia = getSpeed() / 50.f;
        m_bAccelerate = false;
    }


    /*if(glfwGetKey(GLFW_KEY_SPACE))
        rotate(3.14159265f/);*/

    if(toRotate != 0 && m_fSpeed > 0)
    {
        Core::Vector3 perp;
        perp = Core::rotate(MY_PI/2.f)*m_vDirection3; //vetor perpendicular ao vetor direção.

        Core::Vector3 speed;
        speed = m_vDirection3*m_fSpeed;

        Core::Vector3 sum;
        sum = speed + perp;

        float angle = toRotate*Core::angle(m_vDirection3, Core::unitary(sum))/10.f;
        std::cout << "ANGULO: " << angle << std::endl;
        rotate(angle);
        m_vShotPos3 = Core::rotate(angle)*m_vShotPos3;
    }

    if(m_bAccelerate)
        accelerate();

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
            s->setSpeed(3);
            setShotsPerSecond(2);
            if(!shoot(s))
                delete s;
        }
    }
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

void Player::accelerate()
{
    setSpeed(getSpeed() + getAcceleration());
    if(getSpeed() > getMaxSpeed())
        setSpeed(getMaxSpeed());
}
