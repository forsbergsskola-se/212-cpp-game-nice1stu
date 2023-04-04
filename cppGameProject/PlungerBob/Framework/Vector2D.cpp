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

float CVector2D::Length(void) const
{
	const float XSquared = x * x;
	const float YSquared = y * y;

	return sqrtf(XSquared + YSquared);
}

float CVector2D::Normalize(void)
{
	const float VectorLength = this->Length();

	if(VectorLength != 0.0f)
	{
		this->x = this->x / VectorLength;
		this->y = this->y / VectorLength;
	}

	return VectorLength;
}