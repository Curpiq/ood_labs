#pragma once
#include "IShape.h"

class Rectangle : public IShape
{
private:
	double m_width;
	double m_height;
public:
	Rectangle(double width, double height)
		:m_width(width)
		,m_height(height)
	{
	}

	double GetPerimeter()const
	{
		return (static_cast<double>(m_width) + m_height) * 2;
	}

	double GetArea()const override
	{
		return (static_cast<double>(m_width) * m_height);
	}
};