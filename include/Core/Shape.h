#ifndef _BRUNODEA_CG_T2_SHAPE_H_
#define _BRUNODEA_CG_T2_SHAPE_H_

#include "Core/matrix_functions.hpp"
#include <vector>

namespace Core
{
    class Shape
    {
    public:
        enum Type
        {
            SHAPE_RECT = 0x00000001,
            SHAPE_CIRCLE = 0x00000010
        };
    public:
        Shape();
        Shape(Vector2 &pos);

        virtual bool collides(Shape *shape);
        virtual bool collides(Vector2 &dot) = 0;

        virtual void onRender() = 0;

        inline int getType() { return m_iType; }
        inline Vector2 getPos() { return m_Pos; }
        inline void setPos(Vector2 &pos) { m_Pos = pos; }

        inline void setColor(float r, float g, float b, float a)
        {
            m_Color[0] = r;
            m_Color[1] = g;
            m_Color[2] = b;
            m_Color[3] = a;
        }

        virtual Shape &operator=(Shape &shape) = 0;

        int m_iId; //identifier.

    protected:
        int m_iType;
        Vector2 m_Pos;
        Vector4 m_Color;
    }; //Shape
} //Core
#endif // _AZoMe_SHAPE_H_
