#pragma once
#include "IShape.h"
#define _USE_MATH_DEFINES
#include <math.h>

class CCircle : public IShape
{
	private:
		CircleShape m_circle;
	public:
		CCircle(CircleShape&& circle)
			:m_circle(std::move(circle))
		{
		}

		double GetPerimeter()const override 
		{ 
			return 2 * static_cast<double>(m_circle.getRadius()) * M_PI;
		}

		double GetArea()const override
		{ 
			return pow(m_circle.getRadius(), 2) * M_PI;
		}

		const Shape& GetSFShape()const override
		{
			return m_circle;
		}
};