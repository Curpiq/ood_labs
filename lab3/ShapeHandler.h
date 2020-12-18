#pragma once
#pragma once
#include "stdfx.h"
#include "IShape.h"

class ShapeHandler
{
public:
	//запрещ€ем копирование и присваивание экземпл€ров
	ShapeHandler(const ShapeHandler&) = delete;
	ShapeHandler& operator=(const ShapeHandler&) = delete;

	static ShapeHandler& GetInstance(std::istream& input);

	void HandleCommand();

	const std::vector<std::shared_ptr<IShape>>& GetShapesList()const;
private:
	//приватный конструктор запрашивает создание экземпл€ра в обход GetInstance()
	ShapeHandler(std::istream& input);

	void GetRectangleData(std::istream& args);
	void GetCircleData(std::istream& args);
	void GetTriangleData(std::istream& args);
private:
	using Handler = std::function<void(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	const ActionMap m_actionMap;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};
