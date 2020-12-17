#pragma once
#include <sstream>
#include <map>
#include <functional>
#include <vector>
#include "IShape.h"

class ShapeHandler
{
public:
	//запрещяем копирование и присваивание экземпляров
	ShapeHandler(const ShapeHandler&) = delete;
	ShapeHandler& operator=(const ShapeHandler&) = delete;

	static ShapeHandler& GetInstance(std::istream& input, std::ostream& output);

	void HandleCommand();
	void DisplayShapes()const;

private:
	//приватный конструктор запрашивает создание экземпляра в обход GetInstance()
	ShapeHandler(std::istream& input, std::ostream& output);

	void GetRectangleData(std::istream& args);
	void GetCircleData(std::istream& args);
	void GetTriangleData(std::istream& args);
private:
	using Handler = std::function<void(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	std::vector<std::shared_ptr<IShape>> shapes;
};
