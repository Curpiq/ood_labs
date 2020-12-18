#pragma once
#include "SFML/Graphics.hpp"
#include "IShapeVisitor.h"

class IShape
{
public:
	virtual ~IShape() {};
	virtual double GetPerimeter()const = 0;
	virtual double GetArea()const = 0;
	virtual const sf::Shape& GetSFShape()const = 0;
	virtual void Accept(IShapeVisitor& visitor)const = 0;
};
