#include "Core/Shape.h"
#include "Core/shape_functions.h"

using namespace Core;

Shape::Shape()
{
    m_Color.clear(0);
    m_Color[0] = 1.f;

    m_iId = -1;
}

Shape::Shape(Vector2 &pos)
    : m_Pos(pos)
{
    m_Color.clear(0);
    m_Color[1] = 1.f;

    m_iId = -1;
}

bool Shape::collides(Shape *shape)
{
    if(shape == NULL)
        return false;

    return shapeCollision(this, shape);
}
