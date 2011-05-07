#include "Game/Player.h"
#include "Core/Multishape.h"
#include "Core/ShapeRect.h"
#include "glfw.h"
#include "Core/matrix_functions.hpp"

#include <iostream>

using namespace Game;

Player::Player()
    : Ship()
{
    init();
}

Player::Player(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos)
    : Ship(dir, speed, pos)
{
    init();
}

void Player::init()
{
    m_Type = m_Type & GameObject::PLAYER;
    m_fAcceleration = 0.0003f;
    m_fMaxSpeed = .0003f;

    initMultiShape();
    initVertices();
}

void Player::initMultiShape()
{
    Core::Vector2 pos(0);
    pos[1] = 0.3f;
    Core::ShapeRect *shape = new Core::ShapeRect(pos, .1f, .1f);

    pos[0] = .05f; //.1/2
    pos[1] = 0.f;
    Core::ShapeRect *cannon = new Core::ShapeRect(pos, .0125f, .0125f);

    m_MultiShape.addShape(shape);
    m_MultiShape.addShape(cannon);
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

void Player::onRender()
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

void Player::onCollision(GameObject *obj)
{
}

void Player::onUpdate()
{
    /*
    if(m_fSpeed > 0.f)
        m_fSpeed -= m_fAcceleration; //inércia?
    else
        m_fSpeed = 0.f;
    */
}

void Player::onKeyEvent(int key, int state)
{
    /*
    if(key == GLFW_KEY_UP)
    {
        m_fSpeed += m_fAcceleration;
        if(m_fSpeed > m_fMaxSpeed)
            m_fSpeed = m_fMaxSpeed;
    }
    */
    if(key == GLFW_KEY_RIGHT && state == GLFW_PRESS)
    {
        Core::Vector3 pos = m_vPosition3;
        Core::Matrix3 mat = Core::translate(pos)*Core::rotate(1.f)*Core::translate(Core::Vector3(0));
        adjustVertices(mat);
    }
}

