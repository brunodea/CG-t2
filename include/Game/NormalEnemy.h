#ifndef _BRUNODEA_CG_T2_NORMAL_ENEMY_H_
#define _BRUNODEA_CG_T2_NORMAL_ENEMY_H_

#include "macros.h"
#include "Game/Enemy.h"
#include "Game/GameController.h"
#include "Game/Player.h"

namespace Game
{
    class NormalEnemy : public Enemy
    {
    public:
        NormalEnemy() : Enemy(Enemy::NORMAL_ENEMY) { init(); }
        NormalEnemy(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos) 
            : Enemy(dir, speed, pos, Enemy::NORMAL_ENEMY)
        { init(); }

        void onCollision(GameObject *go)
        {
        }
        void update()
        {
            if(m_pVictim == NULL)
                return;

            Core::Vector3 vic_pos = m_pVictim->getPos();
            Core::Vector2 ppos2;
            ppos2[0] = vic_pos[0];
            ppos2[1] = vic_pos[1];

            rotateInDirectionOf(ppos2);
            if(isInSight(ppos2))
            {
                NormalShot *s = new NormalShot();
                Core::Vector3 v = m_vShotPos3;
                v += m_vPosition3;
                v[2] = 1;
                s->setPos(v);
                s->setDirection(m_vDirection3);
                s->setSpeed(8);
                setShotsPerSecond(3);
                if(!shoot(s))
                    delete s;
            }
            accelerate(true);
            move();
        }

    private:
        void init()
        {
            setVisible(true);
            m_fAcceleration = .3;
            m_fMaxSpeed = 5;
            Core::Vector3 v(1);
            v[0] = 0.f;
            v[1] = -1.f;
            setDirection(v);
            m_iImage = TextureID::m_sTextureID[TEX_NORMAL_ENEMY];

            float w = 52/3;
            float h = 56/3;
            initVertices(w, h);
            m_vShotPos3[0] = m_vPosition3[0];
            m_vShotPos3[1] = m_vPosition3[1] - h;

            rotate(MY_PI);
        }

    }; //end of class NormalEnemy.
} //end of namespace Game.
#endif
