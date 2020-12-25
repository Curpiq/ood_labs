#pragma once

#include "Rectangle.h"
#include <memory>
#include "SFML/Graphics.hpp"

class RectangleCreator
{
private:
	//приватный конструктор запрашивает создание экземпл€ра в обход GetInstance()
	RectangleCreator()
	{
	}
public:
	static RectangleCreator& GetInstance()
	{
		static RectangleCreator instance;
		return instance;
	}
	//запрещ€ем копирование и присваивание экземпл€ров
	RectangleCreator(const RectangleCreator&) = delete;
	RectangleCreator& operator=(const RectangleCreator&) = delete;

	std::shared_ptr <IShape> CreateShape(sf::RectangleShape& rectangle)
	{
		double width = rectangle.getSize().x;
		double height = rectangle.getSize().y;

		auto rect = FactoryMethod(width, height);
		return rect;
	}

	std::shared_ptr<IShape> FactoryMethod(double width, double height)const
	{
		auto rect = std::make_shared<Rectangle>(width, height);
		return rect;
	}
};