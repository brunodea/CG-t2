#ifndef _BRUNODEA_CG_T2_SHAPE_CIRC_H_
#define _BRUNODEA_CG_T2_SHAPE_CIRC_H_

#include "Core/Shape.h"
#include "Core/matrix_functions.hpp"

namespace Core
{
    class ShapeCirc : public Shape
    {
    public:
        ShapeCirc(Vector2 &pos, double rad);

        inline double getRadius() { return m_iRadius; }
        void onRender();

        Shape &operator=(Shape &shape);

        bool collides(Vector2 &dot);

    private:
        double m_iRadius;
    }; //ShapeCirc.
} //Core.

#endif // _AZoMe_SHAPECIRC_H_
