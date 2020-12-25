#pragma once
#include "IShapeVisitor.h"

class IShape
{
public:
	virtual ~IShape() {};
	virtual double GetPerimeter()const = 0;
	virtual double GetArea()const = 0;
	virtual void PrintInfo(IShapeVisitor& visitor)const = 0;
};
