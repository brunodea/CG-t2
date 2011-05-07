#ifndef _BRUNODEA_CG_T2_SHAPE_FUNCTIONS_H_
#define _BRUNODEA_CG_T2_SHAPE_FUNCTIONS_H_

#include <vector>

#include "Core/matrix_functions.hpp"
#include "Core/ShapeRect.h"
#include "Core/ShapeCirc.h"
#include "Core/Shape.h"
#include "Game/GameObject.hpp"

bool shapeCollision(Core::Shape *shapeA, Core::Shape *shapeB);

bool rectToRectCol(Core::ShapeRect *rectA, Core::ShapeRect *rectB);
bool rectToCircCol(Core::ShapeRect *rect, Core::ShapeCirc *circ);
bool circToCircCol(Core::ShapeCirc *circA, Core::ShapeCirc *circB);

float pointsDistance(Core::Vector2 &dotA, Core::Vector2 &dotB);

#endif // _BRUNODEA_CG_T2_SHAPE_FUNCTIONS_H_
