#ifndef _BRUNODEA_CG_T2_SHIP_HPP_
#define _BRUNODEA_CG_T2_SHIP_HPP_

/*
 * Interface base para qualquer nave.
 * No fim, eh apenas um gameobject que pode dar tiro.
 */

#include "Game/GameObject.hpp"
#include "Game/Shot.hpp"
#include "Core/matrix_functions.hpp"

#include <vector>

namespace Game
{
    class Ship : public GameObject
    {
    public:
        Ship(Type type);
        Ship(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos, Type type);
        ~Ship();

        void onUpdate();

        /*************************/
        /*  Virtual Functions    */
        /*************************/
        virtual void onRender(); /* Fun��o chamada ap�s a renderiza��o b�sica. */
        virtual void onCollision(GameObject *obj) = 0;
        virtual void onKeyEvent(int key, int state) {/**/}

        /* Setters & Getters */

        inline void setShotsPerSecond(unsigned int sps) { m_iShotsPerSecond = sps; }
    protected:
        /* true se o tiro foi dado. */
        bool shoot(Shot *s);

    protected:
        std::vector<Shot *> *m_vpShots; //vetor de tiros.
        double m_dLastShot;
        unsigned int m_iShotsPerSecond; //numero m�ximo de tiros por segundo.

    private:
        
        virtual void update() = 0; //chamada no fim da fun��o membro onUpdate que faz o update b�sico.
        inline void addShot(Shot *shot) { m_vpShots->push_back(shot); }
    }; //end of class Ship.

} //end of namespace Game.

#endif
