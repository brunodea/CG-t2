#ifndef _BRUNODEA_CG_T2_SHAPE_RECT_H_
#define _BRUNODEA_CG_T2_SHAPE_RECT_H_

#include "Core/Shape.h"
#include "Core/matrix_functions.hpp"

namespace Core
{
    class ShapeRect : public Shape
    {
    public:
        ShapeRect(Vector2 &pos, int width, int height);

        bool collides(Vector2 &dot);

        void onRender();

        inline int getWidth() { return m_iWidth; }
        inline int getHeight() { return m_iHeight; }

        Shape &operator=(Shape &shape);

    private:
        int m_iWidth;
        int m_iHeight;
    }; //ShapeRect
} //Core

#endif
