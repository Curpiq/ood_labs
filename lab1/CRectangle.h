#pragma once
#include "IShape.h"

class CRectange : public IShape
{
	public:
		CRectange(RectangleShape& rectangle)
			: m_rectangle(rectangle)
		{
		}

		double GetPerimeter()const override
		{
			return (m_rectangle.getSize().x + m_rectangle.getSize().y) * 2;
		}

		double GetArea()const override
		{
			return (m_rectangle.getSize().x * m_rectangle.getSize().y);
		}

	private:
		RectangleShape m_rectangle;
};
