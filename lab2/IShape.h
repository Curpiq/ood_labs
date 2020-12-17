#pragma once
#include "SFML/Graphics.hpp"

class IShape
{
public:
	virtual ~IShape() {};
	virtual double GetPerimeter()const = 0;
	virtual double GetArea()const = 0;
	virtual const sf::Shape& GetSFShape()const = 0;
};
