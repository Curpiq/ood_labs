#pragma once
#include "IShape.h"
#include "GetDistance.h"
#include <iostream>

class CTriangle : public IShape
{
	private:
		ConvexShape m_triangle;
	public:
		CTriangle(ConvexShape&& triangle)
			: m_triangle(std::move(triangle))
		{
		}

		double GetPerimeter()const override
		{
			return GetDistance(m_triangle.getPoint(0), m_triangle.getPoint(1)) +
				GetDistance(m_triangle.getPoint(1), m_triangle.getPoint(2)) +
				GetDistance(m_triangle.getPoint(0), m_triangle.getPoint(2));
		}

		double GetArea()const override
		{
			double halfPerimeter = GetPerimeter() / 2;
			return sqrt(halfPerimeter * (halfPerimeter - GetDistance(m_triangle.getPoint(0), m_triangle.getPoint(1))) *
				(halfPerimeter - GetDistance(m_triangle.getPoint(1), m_triangle.getPoint(2))) *
				(halfPerimeter - GetDistance(m_triangle.getPoint(0), m_triangle.getPoint(2))));
		}
};