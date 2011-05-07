#include "Core/MultiShape.h"

using namespace Core;

MultiShape::MultiShape()
{
    init();
}

void MultiShape::init()
{
    m_pShapeList = new std::vector<Shape *>();
}

MultiShape::~MultiShape()
{
    if(m_pShapeList != NULL)
    {
        unsigned int size = m_pShapeList->size();
        for(unsigned int i = 0; i < size; i++)
            delete m_pShapeList->at(i);
        m_pShapeList->clear();
        m_pShapeList = NULL;
    }
}

//@return NULL if didnt collide. The shape if collided.
Shape *MultiShape::collides(Shape *shape)
{
    if(shape == NULL) return NULL;

    unsigned int size = m_pShapeList->size();
    for(unsigned int i = 0; i < size; i++)
    {
        Shape *s = m_pShapeList->at(i);

        Vector2 oldPos(s->getPos());
        Vector2 newPos;
        newPos[0] = m_RelPos[0] + s->getPos()[0];
        newPos[1] = m_RelPos[1] + s->getPos()[1];
        s->setPos(newPos);
        bool collided = shape->collides(s);
        s->setPos(oldPos);

        if(collided)
            return s;
    }
    return NULL;
}

Shape *MultiShape::collides(MultiShape *mshape)
{
    if(mshape == NULL) return NULL;

    unsigned int size = mshape->getShapeList()->size();
    for(unsigned i = 0; i < size; i++)
    {
        Shape *shape = mshape->getShapeList()->at(i);
        Vector2 oldPos(shape->getPos());
        Vector2 newPos;
        newPos[0] = shape->getPos()[0] + mshape->getRelPos()[0];
        newPos[1] = shape->getPos()[1] + mshape->getRelPos()[1];
        shape->setPos(newPos);
        Shape *shapeCol = collides(shape);
        shape->setPos(oldPos);
        if(shapeCol != NULL)
            return shapeCol;
    }
    return false;
}

void MultiShape::onRender()
{
    unsigned int size = m_pShapeList->size();
    for(unsigned int i = 0; i < size; i++)
    {
        Shape *s = m_pShapeList->at(i);

        Vector2 oldPos(s->getPos());
        Vector2 newPos;
        newPos[0] = m_RelPos[0] + s->getPos()[0];
        newPos[1] = m_RelPos[1] + s->getPos()[1];
        s->setPos(newPos);

        s->onRender();

        s->setPos(oldPos);
    }
}
