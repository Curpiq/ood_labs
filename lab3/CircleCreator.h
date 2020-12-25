#pragma once

#include <memory>
#include "SFML/Graphics.hpp"
#include "Circle.h"

class CircleCreator
{
private:
	//приватный конструктор запрашивает создание экземпл€ра в обход GetInstance()
	CircleCreator()
	{
	}
public:
	static CircleCreator& GetInstance()
	{
		static CircleCreator instance;
		return instance;
	}
	//запрещ€ем копирование и присваивание экземпл€ров
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