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
            bool toRotate = false;
            float pi = 3.14159265f;
            int c = 0;
            int w;
            int h;
            glfwGetWindowSize(&w, &h);
            if(m_vPosition3[0] < 0)
            {
                m_vPosition3[0] = w-c;
                toRotate = true;
            }
            else if(m_vPosition3[0] > w)
            {
                m_vPosition3[0] = c;
                toRotate = true;
            }
            if(m_vPosition3[1] < 0)
            {
                m_vPosition3[1] = h-c;
                toRotate = true;
            }
            else if(m_vPosition3[1] > h)
            {
                m_vPosition3[1] = c;
                toRotate = true;
            }

            std::vector<std::vector<Shot *>::iterator> deadShots;
            for(std::vector<Shot *>::iterator it = m_vpShots->begin(); it != m_vpShots->end(); it++)
            {
                Shot *s = *it;
                if(s->isAlive())
                    s->onUpdate();
                else
                    deadShots.push_back(it);
                //else //se o tiro não existir mais, ele é removido do vetor de tiros.
                //    m_vpShots->erase(it);
                //if(m_vpShots->empty())
                //    break;
            }
            for(unsigned int i = 0; i < deadShots.size(); i++)
                m_vpShots->erase(deadShots.at(i));

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

        /* Ângulo de rotação varia de acordo com a velocidade. */
        float rotateToDir(bool right)
        {
            int toRotate = 1;
            if(!right)
                toRotate *= -1;
            Core::Vector3 perp;
            perp = Core::rotate(MY_PI/2.f)*m_vDirection3; //vetor perpendicular ao vetor direção.

            Core::Vector3 speed;
            speed = m_vDirection3*m_fSpeed;

            Core::Vector3 sum;
            sum = speed + perp;

            float angle = toRotate*Core::angle(m_vDirection3, Core::unitary(sum))/10.f;
            rotate(angle);

            return angle;
        }

        /* Setters & Getters */
        inline float getAcceleration() { return m_fAcceleration; }
        inline void setAcceleration(float acc) { m_fAcceleration = acc; }

        inline float getMaxSpeed() { return m_fMaxSpeed; }
        inline void setMaxSpeed(float max_speed) { m_fMaxSpeed = max_speed; }

        inline void setShotsPerSecond(unsigned int sps) { m_iShotsPerSecond = sps; }
    protected:
        void accelerate(bool up)
        {
            float v = 1;
            if(!up)
                v *= 1/(-7.f);

            setSpeed(getSpeed() + (v*getAcceleration()));
            if(getSpeed() > getMaxSpeed())
                setSpeed(getMaxSpeed());
            else if(getSpeed() < 0.f)
                setSpeed(0.f);
        }

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
