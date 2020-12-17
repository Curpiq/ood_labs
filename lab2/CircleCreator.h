#pragma once
#include "Circle.h"

class CircleCreator
{
private:
	//приватный конструктор запрашивает создание экземпляра в обход GetInstance()
	CircleCreator()
	{
	}
public:
	static CircleCreator& GetInstance()
	{
		static CircleCreator instance;
		return instance;
	}
	//запрещяем копирование и присваивание экземпляров
	CircleCreator(const CircleCreator&) = delete;
	CircleCreator& operator=(const CircleCreator&) = delete;

	std::shared_ptr<IShape> CreateShape(sf::CircleShape&& circle)const
	{
		auto rect = std::make_shared<Circle>(std::move(circle));
		return rect;
	}
};