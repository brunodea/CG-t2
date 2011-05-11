#ifndef _BRUNODEA_CG_T2_GAME_OBJECT_HPP_
#define _BRUNODEA_CG_T2_GAME_OBJECT_HPP_

/*
 * Interface que lida com todo o tipo de GameObject no jogo. 
 */

#include "Core/matrix_functions.hpp"
#include "glfw.h"
#include "FPS.hpp"

#include <vector>

namespace Game
{
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

        void render();

        inline void move()
        {
            Core::Vector3 pos = toVector(m_vDirection3*m_fSpeed*FPS::instance().getInterpolation());
            m_vPosition3 += pos;
        }

        void rotateInDirectionOf(const Core::Vector2 &vec); //faz o gameobject se rotacionar na direção de vec com uma latencia.
        bool isInSight(const Core::Vector2 &vec); //true se vec está na mira.

        /***********************
         *  Virtual Functions  *
         ***********************/
        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onCollision(GameObject *obj) = 0;
        virtual void onKeyEvent(int key, int state) {/**/}
        virtual void onMousePosEvent(int x, int y) 
        {
            m_Mouse[0] = x;
            m_Mouse[1] = y;
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
        inline int getType() { return m_iType; }
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
        Core::Vector2 m_Mouse;

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
    

    inline bool isInsideWindow(Core::Vector2 &v)
    {
        int width;
        int height;
        glfwGetWindowSize(&width, &height);
        if(v[0] < 0 || v[0] > width || v[1] < 0 || v[1] > height)
            return false;
        return true;
    }
    inline bool isInsideWindow(Core::Vector3 &vec)
    {
        Core::Vector2 v;
        v[0] = vec[0];
        v[1] = vec[1];
        return isInsideWindow(v);
    }

} //end of namespace Game.

#endif
