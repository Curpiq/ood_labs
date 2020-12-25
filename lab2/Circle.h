#pragma once
#include <SFML/Graphics.hpp>
#include "IShape.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Circle : public IShape
{
private:
	sf::Vector2f m_center;
	double m_radius;
public:
	Circle(sf::Vector2f center, double radius)
		:m_center(center)
		, m_radius(radius)
	{
	}

	double GetPerimeter()const override
	{
		return 2 * m_radius * M_PI;
	}

	double GetArea()const override
	{
		return pow(m_radius, 2) * M_PI;
	}
};