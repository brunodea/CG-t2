#ifndef _BRUNODEA_CG_T2_SHOT_HPP_
#define _BRUNODEA_CG_T2_SHOT_HPP_

/*
 * Interface Shot. Lida com os tipos de tiro.
 */

#include "Game/GameObject.hpp"
#include "Core/matrix_functions.hpp"
#include "Game/TextureID.hpp"
#include "macros.h"

namespace Game
{
    class Shot : public GameObject
    {
    public:
        enum Type
        {
            NORMAL = 0
        }; //end of enum Type.

    public:
        Shot(unsigned int damage, Type type) : GameObject(GameObject::SHOT | type), m_iDamage(damage) 
        {
            setVisible(false);
        }

        virtual void onUpdate() 
        {
            if(isVisible())
            {
                if(!isInsideWindow()) //se o tiro saiu da tela, marcar ele como morto para ser removido depois.
                    setLifes(0);
                move();
            }
        }
        virtual void onCollision(GameObject *obj) 
        {
            if(isVisible() && isAlive())
            {
                obj->setLifes(obj->getLifes() - m_iDamage);
                setLifes(0);
            }
        }

    private:
        unsigned int m_iDamage; //quanto de dano o tiro causa.
    }; //end of class Shot.


    /* Tiro Comum. */
    struct NormalShot : public Shot
    {
        NormalShot() : Shot(1, Shot::NORMAL) 
        {
            m_iImage = TEXTURES[TEX_NORMAL_SHOT];

            initVertices(13/3, 11/3);
        }

    }; //end of struct NormalShot.
} //end of namespace Game.

#endif
