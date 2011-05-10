#include "Game/Ship.hpp"
#include "Core/matrix_functions.hpp"

using namespace Game;

Ship::Ship(Type type) 
    : GameObject(GameObject::SHIP | type), m_dLastShot(0), m_iShotsPerSecond(2)
{
    m_fAcceleration = 0;
    m_fMaxSpeed = 0;
    m_vpShots = new std::vector<Shot *>();
}

Ship::Ship(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos, Type type)
    : GameObject(dir, speed, pos, GameObject::SHIP & type), m_dLastShot(0), m_iShotsPerSecond(2)
{
    m_fAcceleration = 0;
    m_fMaxSpeed = 0;
    m_vpShots = new std::vector<Shot *>();
}

Ship::~Ship()
{
    for(unsigned int i = 0; i < m_vpShots->size(); i++)
        delete m_vpShots->at(i);
    m_vpShots->clear();
    delete m_vpShots;
}

void Ship::onRender()
{
    for(unsigned int i = 0; i < m_vpShots->size(); i++)
    {
        Shot *s = m_vpShots->at(i);
        if(s->isAlive())
            s->render();
    }
}

void Ship::onUpdate()
{
    int c = 3;
    int w;
    int h;
    glfwGetWindowSize(&w, &h);
    if(m_vPosition3[0] < 0)
        m_vPosition3[0] = w+c;
    else if(m_vPosition3[0] > w)
        m_vPosition3[0] = -c;
    if(m_vPosition3[1] < 0)
        m_vPosition3[1] = h+c;
    else if(m_vPosition3[1] > h)
        m_vPosition3[1] = -c;

    for(std::vector<Shot *>::iterator it = m_vpShots->begin(); it != m_vpShots->end(); it++)
    {
        Shot *s = *it;
        if(s->isAlive())
            s->onUpdate();
        else
        {
            delete *it;
            m_vpShots->erase(it);
            break;
        }
    }
    
    update();
}

bool Ship::shoot(Shot *s)
{ 
    double time = glfwGetTime();
    if(time - m_dLastShot > 1.f/m_iShotsPerSecond) //m_iShotsPerSecond por segundo no máximo.
    {
        m_dLastShot = time;

        s->setVisible(true);
        addShot(s);
        return true;
    }
    return false;
}
