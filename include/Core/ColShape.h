#ifndef _BRUNODEA_CG_T2_COL_SHAPE_H_
#define _BRUNODEA_CG_T2_COL_SHAPE_H_

#include "Core/matrix_functions.hpp"
//#include "Core/shape_functions.h"

namespace Core
{
    class ColShape;
    class CircleShape;

    inline bool circToCircCol(CircleShape *circA, CircleShape *circB);
    inline float pointsDistance(Vector2 &dotA, Vector2 &dotB);

    class ColShape
    {
    public:
        enum Type
        {
            CIRCLE = 0
        }; //end of enum Type.

    public:
        ColShape(Type type) : m_Type(type), m_vPosition3(0) {}

        virtual bool collided(ColShape &shape) = 0;

        inline void setPos(Vector3 &pos) { m_vPosition3 = pos; }
        inline Vector3 getPos() { return m_vPosition3; }

        inline Type getType() { return m_Type; }

    private:
        Type m_Type;
        Vector3 m_vPosition3;

    }; //end of class ColShape.


    class CircleShape : public ColShape
    {
    public:
        CircleShape(float rad) : ColShape(ColShape::CIRCLE) { setPos(Vector3(0)); }
        CircleShape(float rad, Vector3 &pos) : ColShape(ColShape::CIRCLE) { setPos(pos); }

        bool collided(ColShape &shape) const;

        float getRadius() { return m_fRadius; }

    private:
        float m_fRadius;
    }; //end of struct Circle.


    bool CircleShape::collided(ColShape &shape) const
    {
        switch(shape.getType())
        {
        case CIRCLE:
            return circToCircCol((CircleShape *) this, (CircleShape *) &shape);
        }

        return false;
    }

    inline bool circToCircCol(CircleShape *circA, CircleShape *circB)
    {
        if(circA == NULL || circB == NULL)
            return false;

        Vector2 pos_a;
        pos_a[0] = circA->getPos()[0];
        pos_a[1] = circA->getPos()[1];
        Vector2 pos_b;
        pos_b[0] = circB->getPos()[0];
        pos_b[1] = circB->getPos()[1];

        if(circA->getRadius() + circB->getRadius() >=
           pointsDistance(pos_a, pos_b))
            return true;
        return false;
    }

    inline float pointsDistance(Vector2 &dotA, Vector2 &dotB)
    {
        float diff_x = dotB(0,0) - dotA(0,0);
        float diff_y = dotB(1,0) - dotA(1,0);
        float delta = (diff_x*diff_x) + (diff_y*diff_y);
        return sqrt(delta);
    }

} //end of namespace Core.

#endif
