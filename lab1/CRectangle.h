#pragma once
#include "IShape.h"

class CRectange : public IShape
{
	private:
		RectangleShape m_rectangle;
	public:
		CRectange(RectangleShape&& rectangle)
			: m_rectangle(std::move(rectangle))
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
};
