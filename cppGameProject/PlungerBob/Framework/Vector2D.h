#pragma once

class CVector2D
{
public:
	
	 CVector2D				(void);
	 CVector2D				(const float X, const float Y);
	~CVector2D				(void);

	CVector2D operator -	(void) const
	{
		return CVector2D(-x, -y);
	}

	CVector2D operator +	(const CVector2D& rIn) const
	{
		return CVector2D(x + rIn.x, y + rIn.y);
	}

	CVector2D operator -	(const CVector2D& rIn) const
	{
		return CVector2D(x - rIn.x, y - rIn.y);
	}

	CVector2D operator *	(const CVector2D& rIn) const
	{
		return CVector2D(x * rIn.x, y * rIn.y);
	}

	CVector2D operator *	(const float Scalar) const
	{
		return CVector2D(x * Scalar, y * Scalar);
	}

	CVector2D operator /	(const float Scalar) const
	{
		return CVector2D(x / Scalar, y / Scalar);
	}
	
	CVector2D& operator +=	(const CVector2D& rIn)
	{
		x += rIn.x;
		y += rIn.y;

		return *this;
	}

	CVector2D& operator -=	(const CVector2D& rIn)
	{
		x -= rIn.x;
		y -= rIn.y;

		return *this;
	}

	CVector2D& operator *=	(const CVector2D& rIn)
	{
		x *= rIn.x;
		y *= rIn.y;

		return *this;
	}

	CVector2D& operator /=	(const CVector2D& rIn)
	{
		x /= rIn.x;
		y /= rIn.y;

		return *this;
	}

	CVector2D& operator +=	(const float In)
	{
		x += In;
		y += In;

		return *this;
	}

	CVector2D& operator -=	(const float In)
	{
		x -= In;
		y -= In;

		return *this;
	}

	CVector2D& operator *=	(const float In)
	{
		x *= In;
		y *= In;

		return *this;
	}

	CVector2D& operator /=	(const float In)
	{
		x /= In;
		y /= In;

		return *this;
	}

public:

	float Length			(void) const;
	
	float Normalize			(void);

public:

	float x;
	float y;

	static const CVector2D Zero;

};