#pragma once

#include "Triangle.h"

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

	std::shared_ptr<IShape> CreateShape(sf::Vector2f& vertex1, sf::Vector2f& vertex2, sf::Vector2f& vertex3)
	{
		auto tri = std::make_shared<Triangle>(vertex1, vertex2, vertex3);
		return tri;
	}
};