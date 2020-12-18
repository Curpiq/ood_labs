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

	std::shared_ptr<IShape> CreateShape(sf::Vector2f center, float radius)const
	{
		auto circle_ptr = std::make_shared<Circle>(center, radius);
		return circle_ptr;
	}
};