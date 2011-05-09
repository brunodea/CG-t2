#ifndef _BRUNODEA_CG_T2_GAME_OBJECT_HPP_
#define _BRUNODEA_CG_T2_GAME_OBJECT_HPP_

#include "Core/matrix_functions.hpp"
#include "glfw.h"

#include "FPS.h"
#include <vector>
namespace Game
{
    struct Mouse
    {
        int x;
        int y;
        
        inline Core::Vector2 &toVector2()
        {
            Core::Vector2 *v = new Core::Vector2();
            v[0] = (float)x;
            v[1] = (float)y;

            return *v;
        }

        inline Core::Vector3 &toVector3()
        {
            Core::Vector3 *v = new Core::Vector3(1);
            v[0] = (float)x;
            v[1] = (float)y;

            return *v;
        }

        inline bool isInsideWindow()
        {
            if(x <= 5 || x >= WINDOW_WIDTH-5 || y <= 5 || y >= WINDOW_HEIGHT-5)
                return false;
            return true;
        }
    }; //end of class mouse.

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
            m_bVisible = true;
        }

        ~GameObject()
        {
            if(m_iImage > -1)
                glDeleteTextures(1, &m_iImage);
        }

        inline bool isAlive() { return m_iLifes > 0; }
        inline bool isInsideWindow()
        {
            int width;
            int height;
            glfwGetWindowSize(&width, &height);
            if(m_vPosition3[0] < 0 || m_vPosition3[0] > width || m_vPosition3[1] < 0 || m_vPosition3[1] > height)
                return false;
            return true;
        }


        void render()
        {
            if(!isVisible())
                return;

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

            onRender();
        }

        inline void move()
        {
            Core::Vector3 pos = toVector(m_vDirection3*(m_fSpeed/**GAME_FPS->getFPS()*/));
            m_vPosition3 += pos;
        }

        /***********************
         *  Virtual Functions  *
         ***********************/
        virtual void onRender() {/**/}
        virtual void onUpdate() = 0;
        virtual void onCollision(GameObject *obj) = 0;
        virtual void onKeyEvent(int key, int state) {/**/}
        virtual void onMousePosEvent(int x, int y) 
        {
            m_Mouse.x = x;
            m_Mouse.y = y;
        }
        virtual void onMouseButtonEvent(int button, int action) {/**/}

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

        inline bool isVisible() { return m_bVisible; }
        inline void setVisible(bool visible) { m_bVisible = visible; }
    protected:
        Core::Vector3 m_vDirection3;
        Core::Vector3 m_vPosition3;
        float m_fSpeed;

        Core::Vector4 m_vColor4;

        std::vector<Core::Vector3> m_vVertices;

        int m_iType;
        bool m_bVisible;
        unsigned int m_iLifes;
        Mouse m_Mouse;

        GLuint m_iImage;

    protected:
        void initVertices(float width, float height)
        {
            Core::Vector3 v1(1);
            v1[0] = width;
            v1[1] = height;

            Core::Vector3 v2(1);
            v2[0] = width;
            v2[1] = -height;

            Core::Vector3 v3(1);
            v3[0] = -width;
            v3[1] = -height;

            Core::Vector3 v4(1);
            v4[0] = -width;
            v4[1] = height;
    
            std::vector<Core::Vector3> *vec = new std::vector<Core::Vector3>();
            vec->push_back(v1);
            vec->push_back(v2);
            vec->push_back(v3);
            vec->push_back(v4);

            setVertices(*vec);
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
            Core::Matrix3 rot = Core::rotate(angle);

            Core::Vector3 n_dir = m_vDirection3;
            n_dir = rot*n_dir;
            setDirection(n_dir);
            //Como os vertices ja estao em relação à origem, não precisa transladar para a origem e depois para o lugar certo.
            adjustVertices(rot);
        }

        /* rotaciona em direção ao ponto dot. */
        float rotateTo(Core::Vector2 &dot)
        {
            Core::Vector2 dir;
            dir[0] = m_vDirection3[0];
            dir[1] = m_vDirection3[1];

            Core::Vector2 pos;
            pos[0] = m_vPosition3[0];
            pos[1] = m_vPosition3[1];

            dot -= pos;
            dot = Core::unitary(dot);

            dir = Core::translate(pos)*dir;
            dir -= pos;

            dir = Core::unitary(dir);

            std::cout << std::endl << "dot: " << dot[0] << ", " << dot[1] << std::endl;
            std::cout << "dir: " << dir[0] << ", " << dir[1] << std::endl;

            float ang = Core::angle(dir, dot);
            std::cout << "ang: " << ang << std::endl << std::endl;
            if(ang != 0)
            {
                rotate((MY_PI/2.f)/10.f);
            }
            //else if(ang > .3f)
            //    rotate(-.03f);
            return ang;
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
            m_bVisible = true;
        }
    }; //end of class GameObject.
} //end of namespace Game.

#endif
