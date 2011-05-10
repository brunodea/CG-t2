#ifndef _BRUNODEA_CG_T2_GAME_OBJECT_HPP_
#define _BRUNODEA_CG_T2_GAME_OBJECT_HPP_

/*
 * Interface que lida com todo o tipo de GameObject no jogo. 
 */

#include "Core/matrix_functions.hpp"
#include "glfw.h"

#include <vector>

namespace Game
{
    //Guarda as informacoes do mouse.
    struct Mouse
    {
        int x;
        int y;
        
        inline bool isInsideWindow()
        {
            int w;
            int h;
            glfwGetWindowSize(&w, &h);
            int offset = 5;
            if(x <= offset || x >= w-offset || y <= offset || y >= h-offset)
                return false;
            return true;
        }
    }; //end of class mouse.

    class GameObject
    {
    public:
        /* Tipos de GameObject. */
        enum Type
        {
            ENEMY = 0x00000000,
            PLAYER = 0x00000001,
            NONE = 0x00000010,
            SHOT = 0x00000100,
            SHIP = 0x00001000
        }; //end of enum Type.

    public:
        GameObject();
        GameObject(int type);
        GameObject(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos, int type);

        ~GameObject();

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


        void render();

        inline void move()
        {
            Core::Vector3 pos = toVector(m_vDirection3*m_fSpeed);
            m_vPosition3 += pos;
        }

        void followMouse(); //faz o gameobject se mover em direcao ao mouse.

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

        inline void setDirection(const Core::Vector3 &dir) { m_vDirection3 = dir; }
        inline Core::Vector3 &getDirection() { return m_vDirection3; }
        
        inline void setSpeed(float speed) { m_fSpeed = speed; }
        inline float getSpeed() { return m_fSpeed; } 

        inline void setPos(const Core::Vector3 &pos) { m_vPosition3 = pos; }
        inline Core::Vector3 &getPos() { return m_vPosition3; }

        inline float getAcceleration() { return m_fAcceleration; }
        inline void setAcceleration(float acc) { m_fAcceleration = acc; }

        inline float getMaxSpeed() { return m_fMaxSpeed; }
        inline void setMaxSpeed(float max_speed) { m_fMaxSpeed = max_speed; }

        inline void setLifes(unsigned int lifes) { m_iLifes = lifes; }
        inline int getLifes() { return m_iLifes; }

        inline void setVertices(std::vector<Core::Vector3> &vertices) { m_vVertices = vertices; }
        inline std::vector<Core::Vector3> &getVertices() { return m_vVertices; }

        inline bool isVisible() { return m_bVisible; }
        inline void setVisible(bool visible) { m_bVisible = visible; }

        inline void setTexture(GLuint id) { m_iImage = id; }
    protected:
        Core::Vector3 m_vDirection3;
        Core::Vector3 m_vPosition3;
        float m_fSpeed;

        float m_fAcceleration;
        float m_fMaxSpeed;

        std::vector<Core::Vector3> m_vVertices; //sempre eh um retangulo onde fica a texture.

        int m_iType;
        bool m_bVisible;
        unsigned int m_iLifes;
        Mouse m_Mouse;

        GLuint m_iImage; //id da textura do gameobject.

    protected:
        float rotateToDir(bool right); /* Ângulo de rotação varia de acordo com a velocidade. */
        void accelerate(bool up); //acelera/freia o gameobject

        void initVertices(float width, float height);

        inline void adjustVertices(Core::Matrix3 &mat) //ajusta os verttices de acordo com a matriz de transformacao mat.
        {
            for(unsigned int i = 0; i < m_vVertices.size(); i++)
            {
                Core::Vector3 *vertex = &m_vVertices.at(i);
                *vertex = mat*(*vertex);
            }
        }

        void rotate(float angle);
        /* rotaciona em direção ao ponto dot. */
        float rotateTo(Core::Vector2 &dot);

        /* Funções virtuais */
        virtual inline void afterRotate(float angle) {/**/} //chamada após rotacionar os elementos básicos do GameObject.

    private:
        //inicializacao basica.
        inline void init()
        {
            Core::Vector3 v_init(0);

            setDirection(v_init);
            setSpeed(0);
            setPos(v_init);

            m_iLifes = 1;
            
            m_iImage = -1;
            m_bVisible = true;
        }
    }; //end of class GameObject.
} //end of namespace Game.

#endif
