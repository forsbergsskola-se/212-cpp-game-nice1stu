#include "Vector2D.h"

#include <math.h>

const CVector2D CVector2D::Zero = CVector2D(0.0f, 0.0f);

CVector2D::CVector2D(void)
: x(0.0f)
, y(0.0f)
{

}

CVector2D::CVector2D(const float X, const float Y)
: x(X)
, y(Y)
{

}

CVector2D::~CVector2D(void)
{

}