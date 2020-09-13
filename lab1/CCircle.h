#pragma once
#include "IShape.h"
#define _USE_MATH_DEFINES
#include <math.h>

class CCircle : public IShape
{
public:
	CCircle(CircleShape& circle)
		:m_circle(circle)
	{
	}

	double GetPerimeter()const override 
	{ 
		return 2 * m_circle.getRadius() * M_PI;
	}

	double GetArea()const override
	{ 
		return pow(m_circle.getRadius(), 2) * M_PI;
	}

private:
	CircleShape m_circle;
};