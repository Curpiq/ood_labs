#pragma once

class IShape
{
public:
	virtual ~IShape() {};
	virtual double GetPerimeter()const = 0;
	virtual double GetArea()const = 0;
};
