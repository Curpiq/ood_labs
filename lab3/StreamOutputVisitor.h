#pragma once
#include "IShapeVisitor.h"
#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

class StreamOutputVisitor : public IShapeVisitor
{
public:
	StreamOutputVisitor(std::ostream& output)
		:m_output(output)
	{
	}

	void Visit(Circle const& circle)const override
	{
		m_output << "Circle: P = " << circle.GetPerimeter() << ", S = " << circle.GetArea() << std::endl;
	}

	void Visit(Rectangle const& rectangle)const override
	{
		m_output << "Rectangle: P = " << rectangle.GetPerimeter() << ", S = " << rectangle.GetArea() << std::endl;
	}
	
	void Visit(Triangle const& triangle)const override
	{
		m_output << "Triangle: P = " << triangle.GetPerimeter() << ", S = " << triangle.GetArea() << std::endl;
	}

private:
	std::ostream& m_output;
};