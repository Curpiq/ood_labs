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

	std::shared_ptr <IShape> CreateShape(sf::CircleShape& circle)
	{
		double radius = circle.getRadius();
		sf::Vector2f center = circle.getPosition();

		auto shape = FactoryMethod(center, radius);
		return shape;
	}
	std::shared_ptr<IShape> FactoryMethod(sf::Vector2f center, double radius)const
	{
		auto rect = std::make_shared<Circle>(center, radius);
		return rect;
	}
};