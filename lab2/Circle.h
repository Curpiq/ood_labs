#pragma once

#include "IShape.h"
#include "SFML/Graphics.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

class Circle : public IShape
{
private:
	sf::CircleShape m_circle;
public:
	Circle(sf::CircleShape&& circle)
		:m_circle(circle)
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

	const sf::Shape& GetSFShape()const override
	{
		return m_circle;
	}
};
