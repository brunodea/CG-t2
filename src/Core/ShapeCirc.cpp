#include "Core/ShapeCirc.h"
#include "Core/shape_functions.h"

using namespace Core;

ShapeCirc::ShapeCirc(Vector2 &pos, double rad)
    : Shape(pos), m_iRadius(rad)
{
    m_iType = Shape::SHAPE_CIRCLE;
}

void ShapeCirc::onRender()
{   
}

Shape &ShapeCirc::operator=(Shape &shape)
{
    if(shape.getType() != Shape::SHAPE_CIRCLE)
        return (*this);

    ShapeCirc *circ = dynamic_cast<ShapeCirc *>(&shape);
    if(circ == NULL)
        return (*this);

    Vector2 pos(circ->getPos());
    m_Pos = pos;
    m_iRadius = circ->getRadius();

    return (*this);
}

bool ShapeCirc::collides(Vector2 &dot)
{
    Vector2 pos(getPos());
    if(pointsDistance(pos, dot) <= m_iRadius)
        return true;
    return false;
}

