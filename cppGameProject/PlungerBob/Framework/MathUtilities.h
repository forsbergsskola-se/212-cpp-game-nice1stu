#pragma once

#define KINDA_SMALL_FLOAT (1.e-4f) // 0.0001f

/**
* Clamps a numeric value between rMin and rMax
*/
template <class T>
inline T MathClamp(const T& rMin, const T& rNumber, const T& rMax)
{
	if(rMin < rMax)
	{
		if(rNumber < rMin)
			return rMin;

		else if(rNumber > rMax)
			return rMax;

		else
			return rNumber;
	}

	else
	{
		if(rNumber < rMax)
			return rMax;

		else if(rNumber > rMin)
			return rMin;

		else
			return rNumber;
	}
}

/**
* Returns the lowest of two numerical values
*/
template <class T>
inline T MathMin(const T& rNumber1, const T& rNumber2)
{
	return ((rNumber1 < rNumber2) ? rNumber1 : rNumber2);
}

/**
* Returns the highest of two numerical values
*/
template <class T>
inline T MathMax(const T& rNumber1, const T& rNumber2)
{
	return ((rNumber1 > rNumber2) ? rNumber1 : rNumber2);
}