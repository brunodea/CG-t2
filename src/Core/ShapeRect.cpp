#include "Core/ShapeRect.h"
#include "Core/shape_functions.h"
#include "glfw.h"

#include <iostream>

using namespace Core;

ShapeRect::ShapeRect(Vector2 &pos, float width, float height)
    : Shape(pos), m_fWidth(width), m_fHeight(height)
{
    m_iType = Shape::SHAPE_RECT;
}

bool ShapeRect::collides(Vector2 &dot)
{
    if(dot[0] >= m_Pos[0] && dot[0] <= m_Pos[0] + m_fWidth &&
       dot[1] >= m_Pos[1] && dot[1] <= m_Pos[1] + m_fHeight)
       return true;
    return false;
}

void ShapeRect::onRender()
{
    glColor3f(1.f, 0.f, 0.f);
    glBegin(GL_QUADS);
        glVertex2f(m_Pos[0]-m_fWidth, m_Pos[1]-m_fHeight);
        glVertex2f(m_Pos[0]-m_fWidth, m_Pos[1]+m_fHeight);
        glVertex2f(m_Pos[0]+m_fWidth, m_Pos[1]+m_fHeight);
        glVertex2f(m_Pos[0]+m_fWidth, m_Pos[1]-m_fHeight);
    glEnd();
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
    m_fWidth = rect->getWidth();
    m_fHeight = rect->getHeight();

    return (*this);
}


