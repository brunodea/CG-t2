#ifndef _BRUNODEA_CG_T2_SHIP_HPP_
#define _BRUNODEA_CG_T2_SHIP_HPP_

#include "Game/GameObject.hpp"
#include "Game/Shot.hpp"
#include "Core/matrix_functions.hpp"

namespace Game
{
    class Ship : public GameObject
    {
    public:
        Ship() : GameObject(GameObject::SHIP) : m_Shot(0) {}
        Ship(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos) 
            : GameObject(dir, speed, pos, GameObject::SHIP), m_Shot(0) 
        {}

        ~Ship()
        {
            delete m_Shot;
        }

        /*************************/
        /*  Virtual Functions    */
        /*************************/
        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onCollision(GameObject *obj) = 0;
        virtual void onKeyEvent(int key, int state) {/**/}
    private:
        Shot *m_Shot;

    }; //end of class Ship.

} //end of namespace Game.

#endif
