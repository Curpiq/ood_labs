#pragma once
#include "IShape.h"
#include "GetSide.h"
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
			return GetSide(m_triangle.getPoint(0), m_triangle.getPoint(1)) +
				GetSide(m_triangle.getPoint(1), m_triangle.getPoint(2)) +
				GetSide(m_triangle.getPoint(0), m_triangle.getPoint(2));
		}

		double GetArea()const override
		{
			double halfPerimeter = GetPerimeter() / 2;
			return sqrt(halfPerimeter * (halfPerimeter - GetSide(m_triangle.getPoint(0), m_triangle.getPoint(1))) *
				(halfPerimeter - GetSide(m_triangle.getPoint(1), m_triangle.getPoint(2))) *
				(halfPerimeter - GetSide(m_triangle.getPoint(0), m_triangle.getPoint(2))));
		}

		const Shape& GetSFShape()const override
		{
			return m_triangle;
		}
};