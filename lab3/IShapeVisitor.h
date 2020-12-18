#pragma once
#include <memory>
#include "Shapes.h"

class IShapeVisitor
{
public:
	virtual ~IShapeVisitor() {};
	virtual void Visit(Circle const& circle)const = 0;
	virtual void Visit(Rectangle const& rectangle)const = 0;
	virtual void Visit(Triangle const& triangle)const = 0;
};
