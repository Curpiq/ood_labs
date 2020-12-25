#pragma once
#include "Triangle.h"
#include "SFML/Graphics.hpp"
#include <memory>
class TriangleCreator
{
private:
	//приватный конструктор запрашивает создание экземпляра в обход GetInstance()
	TriangleCreator()
	{
	}
public:
	static TriangleCreator& GetInstance()
	{
		static TriangleCreator instance;
		return instance;
	}
	//запрещяем копирование и присваивание экземпляров
	TriangleCreator(const TriangleCreator&) = delete;
	TriangleCreator& operator=(const TriangleCreator&) = delete;

	std::shared_ptr <IShape> CreateShape(sf::ConvexShape& triangle)
	{
		sf::Vector2f vertex1 = triangle.getPoint(0);
		sf::Vector2f vertex2 = triangle.getPoint(1);
		sf::Vector2f vertex3 = triangle.getPoint(1);
		auto shape = FactoryMethod(vertex1, vertex2, vertex3);
		return shape;
	}
	std::shared_ptr<IShape> FactoryMethod(sf::Vector2f vertex1, sf::Vector2f vertex2, sf::Vector2f vertex3)const
	{
		auto circle = std::make_shared<Triangle>(vertex1, vertex2, vertex3);
		return circle;
	}
};
