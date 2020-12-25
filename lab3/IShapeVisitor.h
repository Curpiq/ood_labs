#pragma once

class Circle;
class Rectangle;
class Triangle;

class IShapeVisitor
{
public:
	virtual ~IShapeVisitor() {};
	virtual void Visit(Circle const& circle)const = 0;
	virtual void Visit(Rectangle const& rectangle)const = 0;
	virtual void Visit(Triangle const& triangle)const = 0;
};