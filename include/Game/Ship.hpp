#ifndef _BRUNODEA_CG_T2_SHIP_HPP_
#define _BRUNODEA_CG_T2_SHIP_HPP_

#include "Game/GameObject.hpp"
#include "Game/Shot.hpp"
#include "Core/matrix_functions.hpp"

#include <vector>

namespace Game
{
    class Ship : public GameObject
    {
    public:
        Ship(Type type) 
            : GameObject(GameObject::SHIP | type), m_dLastShot(0), m_fAcceleration(0), m_fMaxSpeed(0), m_iShotsPerSecond(2)
        {
            m_vpShots = new std::vector<Shot *>();
        }
        Ship(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos, Type type)
            : GameObject(dir, speed, pos, GameObject::SHIP & type), m_dLastShot(0), m_fAcceleration(0), m_fMaxSpeed(0), m_iShotsPerSecond(2)
        {
            m_vpShots = new std::vector<Shot *>();
        }

        ~Ship()
        {
            for(unsigned int i = 0; i < m_vpShots->size(); i++)
                delete m_vpShots->at(i);
            m_vpShots->clear();
            delete m_vpShots;
        }

        /*************************/
        /*  Virtual Functions    */
        /*************************/

        /* Função chamada após a renderização básica. */
        virtual void onRender()
        {
            for(unsigned int i = 0; i < m_vpShots->size(); i++)
            {
                Shot *s = m_vpShots->at(i);
                if(s->isAlive())
                    s->render();
            }
        }
        void onUpdate()
        {
            for(std::vector<Shot *>::iterator it = m_vpShots->begin(); it != m_vpShots->end(); it++)
            {
                Shot *s = *it;
                if(s->isAlive())
                    s->onUpdate();
                //else //se o tiro não existir mais, ele é removido do vetor de tiros.
                //    m_vpShots->erase(it);
                //if(m_vpShots->empty())
                //    break;
            }
            update();
        }

        virtual void update() = 0;
        virtual void onCollision(GameObject *obj) = 0;
        virtual void onKeyEvent(int key, int state) {/**/}

        /* true se o tiro foi dado. */
        inline bool shoot(Shot *s) 
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

        /* Setters & Getters */
        inline float getAcceleration() { return m_fAcceleration; }
        inline void setAcceleration(float acc) { m_fAcceleration = acc; }

        inline float getMaxSpeed() { return m_fMaxSpeed; }
        inline void setMaxSpeed(float max_speed) { m_fMaxSpeed = max_speed; }

        inline void setShotsPerSecond(unsigned int sps) { m_iShotsPerSecond = sps; }
    protected:
        std::vector<Shot *> *m_vpShots;
        double m_dLastShot;
        unsigned int m_iShotsPerSecond; //numero máximo de tiros por segundo.

        float m_fAcceleration;
        float m_fMaxSpeed;
    private:
        
        inline void addShot(Shot *shot) { m_vpShots->push_back(shot); }
    }; //end of class Ship.

} //end of namespace Game.

#endif
