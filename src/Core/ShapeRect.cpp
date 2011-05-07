#include "Core/ShapeRect.h"
#include "Core/shape_functions.h"

#include <iostream>

using namespace Core;

ShapeRect::ShapeRect(Vector2 &pos, int width, int height)
    : Shape(pos), m_iWidth(width), m_iHeight(height)
{
    m_iType = Shape::SHAPE_RECT;
}

bool ShapeRect::collides(Vector2 &dot)
{
    if(dot[0] >= m_Pos[0] && dot[0] <= m_Pos[0] + m_iWidth &&
       dot[1] >= m_Pos[1] && dot[1] <= m_Pos[1] + m_iHeight)
       return true;
    return false;
}

void ShapeRect::onRender()
{
}

Shape &ShapeRect::operator=(Shape &shape)
{
    if(shape.getType() != Shape::SHAPE_RECT)
        return (*this);

    ShapeRect *rect = dynamic_cast<ShapeRect *>(&shape);
    if(rect == NULL)
        return (*this);
    m_iType = shape.getType();
    Vector2 pos(rect->getPos());
    m_Pos = pos;
    m_iWidth = rect->getWidth();
    m_iHeight = rect->getHeight();

    return (*this);
}


