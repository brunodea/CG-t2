#include "Core/shape_functions.h"
#include "Game/GameObject.hpp"

#include <cmath>

using namespace Game;
using namespace Core;

bool shapeCollision(Shape *shapeA, Shape *shapeB)
{
    if(shapeA == NULL || shapeB == NULL || shapeA == shapeB)
        return false;

    int types = shapeA->getType() | shapeB->getType();
    if(types & (Shape::SHAPE_RECT | Shape::SHAPE_RECT))
    {
        bool ret = rectToRectCol((ShapeRect *)shapeA, (ShapeRect *)shapeB);
        if(!ret)
            ret = rectToRectCol((ShapeRect *)shapeB, (ShapeRect *)shapeA);
        return ret;
    }
    else if(types & (Shape::SHAPE_CIRCLE | Shape::SHAPE_CIRCLE))
        return circToCircCol((ShapeCirc *)shapeA, (ShapeCirc *)shapeB);
    else if(types & (Shape::SHAPE_CIRCLE | Shape::SHAPE_RECT))
    {
        ShapeCirc *circ = dynamic_cast<ShapeCirc *>(shapeA);
        ShapeRect *rect;
        if(circ == NULL)
        {
            circ = (ShapeCirc *)shapeB;
            rect = (ShapeRect *)shapeA;
        }
        else
            rect = (ShapeRect *)shapeB;
        return rectToCircCol(rect, circ);
    }

    return false;
}

/* Rect to Rect collision. */
bool rectToRectCol(ShapeRect *rectA, ShapeRect *rectB)
{
    if(rectA == NULL || rectB == NULL)
        return false;

    Vector2 pos_a = rectA->getPos();

    Vector2 topLeft(pos_a);
    Vector2 topRight;
    topRight[0] = pos_a[0] + rectA->getWidth();
    topRight[1] = pos_a[1];

    Vector2 bottomLeft;
    bottomLeft[0] = pos_a[0];
    bottomLeft[1] = pos_a[1] + rectA->getHeight();

    Vector2 bottomRight;
    bottomRight[0] = pos_a[0] + rectA->getWidth();
    bottomRight[1] = pos_a[1] + rectA->getHeight();

    if(rectB->collides(topLeft) || rectB->collides(topRight) ||
       rectB->collides(bottomLeft) || rectB->collides(bottomRight))
        return true;

    return false;
}

bool circToCircCol(ShapeCirc *circA, ShapeCirc *circB)
{
    if(circA == NULL || circB == NULL)
        return false;

    Vector2 pos_a = circA->getPos();
    Vector2 pos_b = circB->getPos();

    if(circA->getRadius() + circB->getRadius() >=
       pointsDistance(pos_a, pos_b))
        return true;
    return false;
}

bool rectToCircCol(ShapeRect *rect, ShapeCirc *circ)
{
    Vector2 pos_circ = circ->getPos();
    Vector2 pos_rect = rect->getPos();
    double dx = pos_circ[0] - (pos_rect[0] + ((pos_rect[0] + rect->getWidth()) / 2));
    if(dx < 0)
        dx *= -1;
    double dy = pos_circ[1] - (pos_rect[1] + ((pos_rect[1] + rect->getHeight()) / 2));
    if(dy < 0)
        dy *= -1;

    if(dx > (rect->getWidth() / 2) + circ->getRadius()) return false;
    if(dy > (rect->getHeight() / 2) + circ->getRadius()) return false;
    if(dx <= rect->getWidth() / 2) return true;
    if(dy <= rect->getHeight() / 2) return true;

    double dist = sqrt((dx*dx) + (dy*dy));
    if(dist > circ->getRadius()) return false;

    return true;
}

float pointsDistance(Vector2 &dotA, Vector2 &dotB)
{
    float diff_x = dotB(0,0) - dotA(0,0);
    float diff_y = dotB(1,0) - dotA(1,0);
    float delta = (diff_x*diff_x) + (diff_y*diff_y);
    return sqrt(delta);
}
