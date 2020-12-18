#pragma once

#include "IShape.h"
#include "SFML/Graphics.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

class Circle : public IShape
{
private:
	sf::CircleShape m_circle;
	sf::Vector2f m_center;
	float m_radius;
public:
	Circle(sf::Vector2f center, float radius)
		:m_center(center)
		, m_radius(radius)
	{
		m_circle = sf::CircleShape(radius);
		m_circle.setPosition(center);
	}

	double GetPerimeter()const override
	{
		return 2 * static_cast<double>(m_circle.getRadius()) * M_PI;
	}

	double GetArea()const override
	{
		return pow(m_circle.getRadius(), 2) * M_PI;
	}

	const sf::Shape& GetSFShape()const override
	{
		return m_circle;
	}
	void Accept(IShapeVisitor& visitor)const override
	{
		visitor.Visit(*this);
	}
};