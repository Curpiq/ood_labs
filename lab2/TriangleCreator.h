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

	std::shared_ptr<IShape> CreateShape(sf::ConvexShape&& triangle)
	{
		auto tri = std::make_shared<Triangle>(std::move(triangle));
		return tri;
	}
};