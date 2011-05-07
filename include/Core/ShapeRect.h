#ifndef _BRUNODEA_CG_T2_SHAPE_RECT_H_
#define _BRUNODEA_CG_T2_SHAPE_RECT_H_

#include "Core/Shape.h"
#include "Core/matrix_functions.hpp"

namespace Core
{
    class ShapeRect : public Shape
    {
    public:
        ShapeRect(Vector2 &pos, float width, float height);

        bool collides(Vector2 &dot);

        void onRender();

        inline float getWidth() { return m_fWidth; }
        inline float getHeight() { return m_fHeight; }

        Shape &operator=(Shape &shape);

    private:
        float m_fWidth;
        float m_fHeight;
    }; //ShapeRect
} //Core

#endif
