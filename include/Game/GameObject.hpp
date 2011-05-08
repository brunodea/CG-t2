#ifndef _BRUNODEA_CG_T2_GAME_OBJECT_HPP_
#define _BRUNODEA_CG_T2_GAME_OBJECT_HPP_

#include "Core/matrix_functions.hpp"
#include "glfw.h"

#include "FPS.h"
#include <vector>
namespace Game
{
    class GameObject
    {
    public:
        enum Type
        {
            ENEMY = 0x00000000,
            PLAYER = 0x00000001,
            NONE = 0x00000010,
            SHOT = 0x00000100,
            SHIP = 0x00001000
        }; //end of enum Type.

    public:
        GameObject()
        {
            m_iType = NONE;
            init();
        }
        GameObject(int type) : m_iType(type) { init(); }

        GameObject(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos, int type)
            : m_vDirection3(dir), m_fSpeed(speed), m_vPosition3(pos), m_iType(type)
        {
            m_iLifes = 1;

            m_vColor4[0] = 1.f;
            m_vColor4[1] = 0.f;
            m_vColor4[2] = 0.f;
            m_vColor4[3] = 1.f;
            
            m_iImage = -1;
        }

        ~GameObject()
        {
            if(m_iImage > -1)
                glDeleteTextures(1, &m_iImage);
        }

        inline bool isAlive() { return m_iLifes > 0; }

        /***********************
         *  Virtual Functions  *
         ***********************/

        void onRender()
        {
            //glColor4f(m_vColor4[0], m_vColor4[1], m_vColor4[2], m_vColor4[3]);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glColor4f(1.f, 1.f, 1.f, 1.f);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, m_iImage);
            glBegin(GL_QUADS); //quadrado
                for(unsigned int i = 0; i < m_vVertices.size(); i++)
                {
                    Core::Vector3 vec(1);
                    vec[0] = (m_vVertices.at(i)+m_vPosition3)(0,0);
                    vec[1] = (m_vVertices.at(i)+m_vPosition3)(1,0);
            
                    if(m_iImage >= 0)
                    {
                        if(i == 0)
                            glTexCoord2f(0.f, 0.f);
                        else if(i == 1)
                            glTexCoord2f(0.f, 1.f);
                        else if(i == 2)
                            glTexCoord2f(1.f, 1.f);
                        else if(i == 3)
                            glTexCoord2f(1.f, 0.f);
                    }
                    glVertex2f(vec[0], vec[1]);
                }
            glEnd();
        }

        virtual void onUpdate() = 0;
        virtual void onCollision(GameObject *obj) = 0;
        virtual void onKeyEvent(int key, int state) {/**/}

        /*************************
         *  Setters & Getters    *
         *************************/

        inline void setDirection(const Core::Vector3 &dir) { m_vDirection3 = Core::unitary(dir); }
        inline Core::Vector3 &getDirection() { return m_vDirection3; }
        
        inline void setSpeed(float speed) { m_fSpeed = speed; }
        inline float getSpeed() { return m_fSpeed; } 

        inline void setPos(const Core::Vector3 &pos) { m_vPosition3 = pos; }
        inline Core::Vector3 &getPos() { return m_vPosition3; }

        inline void setLifes(unsigned int lifes) { m_iLifes = lifes; }
        inline int getLifes() { return m_iLifes; }

        inline void setVertices(std::vector<Core::Vector3> &vertices) { m_vVertices = vertices; }
        inline std::vector<Core::Vector3> &getVertices() { return m_vVertices; }

    protected:
        Core::Vector3 m_vDirection3;
        Core::Vector3 m_vPosition3;
        float m_fSpeed;

        Core::Vector4 m_vColor4;

        std::vector<Core::Vector3> m_vVertices;

        int m_iType;

        unsigned int m_iLifes;
        
        GLuint m_iImage;

    protected:
        inline void move()
        {
            Core::Vector3 pos = toVector(m_vDirection3*(m_fSpeed/**GAME_FPS->getFPS()*/));
            m_vPosition3 += pos;
        }

        inline void adjustVertices(Core::Matrix3 &mat)
        {
            for(unsigned int i = 0; i < m_vVertices.size(); i++)
            {
                Core::Vector3 *vertex = &m_vVertices.at(i);
                *vertex = mat*(*vertex);
            }
        }

        void rotate(float angle)
        {
            if(angle == 0)
                return;
            Core::Vector3 orig;
            orig[0] = -m_vPosition3[0];
            orig[1] = -m_vPosition3[1];
            orig[2] = 1.f;

            Core::Matrix3 rot = Core::rotate(angle);

            Core::Vector3 n_dir = m_vDirection3;
            n_dir = rot*n_dir;
            setDirection(n_dir);
            
            Core::Matrix3 mat = rot; //Como os vertices ja estao em relação à origem, não precisa transladar para a origem e depois para o lugar certo.
            adjustVertices(mat);
        }

    private:
        inline void init()
        {
            Core::Vector3 v_init(0);

            setDirection(v_init);
            setSpeed(0);
            setPos(v_init);

            m_iLifes = 1;
            m_vColor4[0] = 1.f;
            m_vColor4[1] = 0.f;
            m_vColor4[2] = 0.f;
            m_vColor4[3] = 1.f;
            
            m_iImage = -1;
        }
    }; //end of class GameObject.
} //end of namespace Game.

#endif
