#pragma once

#include <memory>
#include "SFML/Graphics.hpp"
#include "Triangle.h"

class TriangleCreator
{
private:
	//приватный конструктор запрашивает создание экземпл€ра в обход GetInstance()
	TriangleCreator()
	{
	}
public:
	static TriangleCreator& GetInstance()
	{
		static TriangleCreator instance;
		return instance;
	}
	//запрещ€ем копирование и присваивание экземпл€ров
	TriangleCreator(const TriangleCreator&) = delete;
	TriangleCreator& operator=(const TriangleCreator&) = delete;

	std::shared_ptr <IShape> CreateShape(sf::ConvexShape& triangle)
	{
		sf::Vector2f vertex1 = triangle.getPoint(0);
		sf::Vector2f vertex2 = triangle.getPoint(1);
		sf::Vector2f vertex3 = triangle.getPoint(2);
		auto shape = FactoryMethod(vertex1, vertex2, vertex3);
		return shape;
	}
	std::shared_ptr<IShape> FactoryMethod(sf::Vector2f vertex1, sf::Vector2f vertex2, sf::Vector2f vertex3)const
	{
		auto circle = std::make_shared<Triangle>(vertex1, vertex2, vertex3);
		return circle;
	}
};