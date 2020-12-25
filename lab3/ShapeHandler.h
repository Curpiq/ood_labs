#pragma once

#include "stdfx.h"
#include "ShapeCreators.h"
#include "StreamOutputVisitor.h"

class ShapeHandler
{
public:
	//запрещяем копирование и присваивание экземпляров
	ShapeHandler(const ShapeHandler&) = delete;
	ShapeHandler& operator=(const ShapeHandler&) = delete;

	static ShapeHandler& GetInstance(std::istream& input, StreamOutputVisitor& visitor);

	void HandleCommand();

	const std::vector<std::shared_ptr<sf::Shape>>& GetShapesList()const;
private:
	//приватный конструктор запрашивает создание экземпляра в обход GetInstance()
	ShapeHandler(std::istream& input, StreamOutputVisitor& visitor);

	void GetRectangleData(std::istream& args);
	void GetCircleData(std::istream& args);
	void GetTriangleData(std::istream& args);
private:
	using Handler = std::function<void(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	StreamOutputVisitor& m_visitor;
	const ActionMap m_actionMap;
	std::vector<std::shared_ptr<sf::Shape>> m_shapes;
};