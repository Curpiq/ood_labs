#pragma once
#include "IShape.h"
#include "SFML/Graphics.hpp"
#include "GetDistance.h"

class Triangle : public IShape
{
private:
	sf::ConvexShape m_triangle;
	sf::Vector2f m_vertex1;
	sf::Vector2f m_vertex2;
	sf::Vector2f m_vertex3;
public:
	Triangle(sf::Vector2f vertex1, sf::Vector2f vertex2, sf::Vector2f vertex3)
		:m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{
		m_triangle = sf::ConvexShape(3);
		m_triangle.setPoint(0, m_vertex1);
		m_triangle.setPoint(1, m_vertex2);
		m_triangle.setPoint(2, m_vertex3);
	}

	double GetPerimeter()const override
	{
		return GetDistance(m_vertex1, m_vertex2) +
			GetDistance(m_vertex2, m_vertex3) +
			GetDistance(m_vertex1, m_vertex3);
	}

	double GetArea()const override
	{
		double halfPerimeter = GetPerimeter() / 2;
		return sqrt(halfPerimeter * (halfPerimeter - GetDistance(m_vertex1, m_vertex2)) *
			(halfPerimeter - GetDistance(m_vertex1, m_vertex3)) *
			(halfPerimeter - GetDistance(m_vertex1, m_vertex3)));
	}

	const sf::Shape& GetSFShape()const override
	{
		return m_triangle;
	}
};
