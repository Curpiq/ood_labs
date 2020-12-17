#pragma once

#include "IShape.h"
#include "SFML/Graphics.hpp"

class Rectangle : public IShape
{
private:
	sf::RectangleShape m_rectangle;
public:
	Rectangle(sf::RectangleShape&& rectangle)
		:m_rectangle(std::move(rectangle))
	{
	}

	double GetPerimeter()const override
	{
		return (static_cast<double>(m_rectangle.getSize().x) + m_rectangle.getSize().y) * 2;
	}

	double GetArea()const override
	{
		return (static_cast<double>(m_rectangle.getSize().x) * m_rectangle.getSize().y);
	}

	const sf::Shape& GetSFShape()const override
	{
		return m_rectangle;
	}
};
