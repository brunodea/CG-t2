#ifndef _BRUNODEA_CG_T2_MULTI_SHAPE_H_
#define _BRUNODEA_CG_T2_MULTI_SHAPE_H_

#include <vector>
#include "Core/Shape.h"

namespace Core
{
    /* A shape with many shapes. */
    class MultiShape
    {
    public:
        MultiShape();

        ~MultiShape();

        inline void addShape(Shape *shape)
        {
            if(shape == NULL) return;

            m_pShapeList->push_back(shape);
        }

        Shape *collides(Shape *shape);
        Shape *collides(MultiShape *mshape);
        void onRender();

        inline std::vector<Shape *> *getShapeList() { return m_pShapeList; }
        inline void setRelPos(Vector2 &relPos){ m_RelPos = relPos; }
        inline Vector2 &getRelPos() { return m_RelPos; }

    private:
        void init();

    private:
        std::vector<Shape *> *m_pShapeList;
        Vector2 m_RelPos; //position where the shapes are relative to.
    }; //ShapeCol
} //Core

#endif
