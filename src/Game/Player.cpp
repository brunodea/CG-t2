#include "Game/Player.h"
#include "glfw.h"
#include "Core/matrix_functions.hpp"
#include "Game/Shot.hpp"
#include "Game/TextureID.hpp"
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
    m_iImage = TEXTURES[TEX_PLAYER];

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
    if(glfwGetKey(GLFW_KEY_SPACE))
        followMouse();
    else
        accelerate(false);

    float rotateAngle = 0.f;
    if(glfwGetKey(GLFW_KEY_RIGHT))
        rotateAngle = rotateToDir(true);
    else if(glfwGetKey(GLFW_KEY_LEFT))
        rotateAngle = rotateToDir(false);
    if(glfwGetKey(GLFW_KEY_UP))
        accelerate(true);
    else if(glfwGetKey(GLFW_KEY_DOWN)) //para diminuir a velocidade da nave.
        accelerate(false);
        
    if(m_fSpeed > 0.f)
        move();
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
            s->setSpeed(10);
            setShotsPerSecond(6);
            if(!shoot(s))
                delete s;
        }
    }
}

void Player::onMousePosEvent(int x, int y)
{
    m_Mouse.x = x;
    m_Mouse.y = y;
}

void Player::onMouseButtonEvent(int button, int action)
{
}

//funcao chamada depois de o GameObject (no caso o player) ter sido chamado.
void Player::afterRotate(float angle)
{
    m_vShotPos3 = Core::rotate(angle)*m_vShotPos3;
}
