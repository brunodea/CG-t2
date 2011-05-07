#ifndef _BRUNODEA_CG_T2_GAME_OBJECT_HPP_
#define _BRUNODEA_CG_T2_GAME_OBJECT_HPP_

#include "Core/matrix_functions.hpp"
#include "Core/MultiShape.h"

#include <vector>

namespace Game
{
    class GameObject
    {
    public:
        enum Type
        {
            ENEMY = 0,
            PLAYER,
            OBJECT,
            SHOT
        }; //end of enum Type.

    public:
        GameObject()
        {
            m_Type = OBJECT;
            init();
        }
        GameObject(Type type) : m_Type(type) { init(); }

        GameObject(const Core::Vector3 &dir, const Core::Vector3 &speed, const Core::Vector3 &pos, Type type)
            : m_vDirection3(dir), m_vSpeed3(speed), m_vPosition3(pos), m_Type(type)
        {
            m_iLifes = 1;
        }


        /***********************
         *  Virtual Functions  *
         ***********************/

        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onCollision(GameObject *obj) = 0;
        virtual void onKeyEvent(int key, int state) {/**/}

        /*************************
         *  Setters & Getters    *
         *************************/

        inline void setDirection(const Core::Vector3 &dir) { m_vDirection3 = dir; }
        inline Core::Vector3 &getDirection() { return m_vDirection3; }
        
        inline void setSpeed(const Core::Vector3 &speed) { m_vSpeed3 = speed; }
        inline Core::Vector3 &getSpeed() { return m_vSpeed3; } 

        inline void setPos(const Core::Vector3 &pos) { m_vPosition3 = pos; }
        inline Core::Vector3 &getPos() { return m_vPosition3; }

        inline void setLifes(unsigned int lifes) { m_iLifes = lifes; }
        inline int getLifes() { return m_iLifes; }

        inline Core::MultiShape &getMultiShape() { return m_MultiShape; }

        inline void setVertices(std::vector<Core::Vector3> &vertices) { m_vVertices = vertices; }
        inline std::vector<Core::Vector3> &getVertices() { return m_vVertices; }

    protected:        
        Core::Vector3 m_vDirection3;
        Core::Vector3 m_vSpeed3;
        Core::Vector3 m_vPosition3;

        std::vector<Core::Vector3> m_vVertices;

        Type m_Type;

        unsigned int m_iLifes;

        Core::MultiShape m_MultiShape;
        
    protected:
        virtual void initMultiShape() = 0;

        inline void move()
        {
        }

    private:
        inline void init()
        {
            Core::Vector3 v_init(0);

            setDirection(v_init);
            setSpeed(v_init);
            setPos(v_init);

            m_iLifes = 1;
            m_MultiShape.setRelPos(m_vPosition3);
        }
    }; //end of class GameObject.
} //end of namespace Game.

#endif
