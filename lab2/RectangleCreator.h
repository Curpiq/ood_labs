#pragma once

#include "Rectangle.h"

class RectangleCreator
{
private:
	//приватный конструктор запрашивает создание экземпляра в обход GetInstance()
	RectangleCreator()
	{
	}
public:
	static RectangleCreator& GetInstance()
	{
		static RectangleCreator instance;
		return instance;
	}
	//запрещяем копирование и присваивание экземпляров
	RectangleCreator(const RectangleCreator&) = delete;
	RectangleCreator& operator=(const RectangleCreator&) = delete;

	std::shared_ptr<IShape> CreateShape(sf::RectangleShape&& rectangle)const
	{
		auto rect = std::make_shared<Rectangle>(std::move(rectangle));
		return rect;
	}
};