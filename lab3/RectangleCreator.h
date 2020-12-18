#pragma once
#include "Rectangle.h"

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

	std::shared_ptr<IShape> CreateShape(sf::Vector2f leftTop, sf::Vector2f rightBottom)const
	{
		auto rect = std::make_shared<Rectangle>(leftTop, rightBottom);
		return rect;
	}
};
