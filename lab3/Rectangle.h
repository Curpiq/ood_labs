#pragma once
#include "IShape.h"
#include "SFML/Graphics.hpp"

class Rectangle : public IShape
{
private:
	sf::RectangleShape m_rectangle;
	sf::Vector2f m_leftTop;
	sf::Vector2f m_rightBottom;
	float m_width;
	float m_height;
public:
	Rectangle(sf::Vector2f leftTop, sf::Vector2f rightBottom)
		:m_leftTop(leftTop)
		,m_rightBottom(rightBottom)
	{
		m_width = sqrt(pow((m_rightBottom.x - m_leftTop.x), 2));
		m_height = sqrt(pow((m_leftTop.y - m_rightBottom.y), 2));
		m_rectangle = sf::RectangleShape(sf::Vector2f(m_width, m_height));
		m_rectangle.setPosition(m_leftTop);
	}

	double GetPerimeter()const override
	{
		return (static_cast<double>(m_width) + m_height) * 2;
	}

	double GetArea()const override
	{
		return (static_cast<double>(m_width) * m_height);
	}

	const sf::Shape& GetSFShape()const override
	{
		return m_rectangle;
	}

	void Accept(IShapeVisitor& visitor)const override
	{
		visitor.Visit(*this);
	}
};
