#include "ShapeHandler.h"
#include <boost/algorithm/string.hpp>
#include "ShapeCreators.h"

using namespace std;
using namespace std::placeholders;

ShapeHandler::ShapeHandler(istream& input, ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
				{ "Rectangle", bind(&ShapeHandler::GetRectangleData, this, _1) },
				{ "Circle", bind(&ShapeHandler::GetCircleData, this, _1) },
				{ "Triangle", bind(&ShapeHandler::GetTriangleData, this, _1) }
		})
{
}

ShapeHandler& ShapeHandler::GetInstance(istream& input, ostream& output)
{
	static ShapeHandler instance(input, output);
	return instance;
}

void ShapeHandler::HandleCommand()
{
	string args;
	getline(m_input, args);
	istringstream ss(args);
	string action;
	ss >> action;
	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(ss);
	}
}

void ShapeHandler::GetRectangleData(istream& argsLine)
{
	string args;
	vector<string> points, p1, p2;
	getline(argsLine, args);

	//убираем лишние пробелы и сплитим по оставшимся
	boost::algorithm::trim(args);
	boost::split(points, args, boost::algorithm::is_any_of(" "));

	//p1, p2 - контейнеры для вершин
	boost::split(p1, points[0], boost::algorithm::is_any_of(","));
	boost::split(p2, points[1], boost::algorithm::is_any_of(","));

	//преобразуем в векторы из либы SFML
	sf::Vector2f leftTop = { stof(p1[0]), stof(p1[1]) };
	sf::Vector2f rightBottom = { stof(p2[0]), stof(p2[1]) };

	//получаем экзепляр класса RectangleCreator
	auto& rectCreator = RectangleCreator::GetInstance();

	//создаем экзепляр класса Rectangle с помощью RectangleCreator, заносим в массив фигур
	shared_ptr<IShape> rect_ptr = rectCreator.CreateShape(leftTop, rightBottom);
	m_shapes.push_back(rect_ptr);

	m_output << "Rectangle: P = " << rect_ptr->GetPerimeter() << ", S = " << rect_ptr->GetArea() << endl;
}

void ShapeHandler::GetCircleData(istream& argsLine)
{
	string args;
	vector<string> params, center;
	getline(argsLine, args);

	//убираем лишние пробелы и сплитим по оставшимся
	boost::algorithm::trim(args);
	boost::split(params, args, boost::algorithm::is_any_of(" "));

	//center - контейнер для точки центра
	boost::split(center, params[0], boost::algorithm::is_any_of(","));

	float radius = stof(params[1]);

	//преобразуем в вектор из либы SFML
	sf::Vector2f pointCenter = { stof(center[0]), stof(center[1]) };

	//получаем экзепляр класса CicleCreator
	auto& circleCreator = CircleCreator::GetInstance();

	//создаем экземпляр класса Circle с помощью CircleCreator, заносим в массив фигур
	std::shared_ptr<IShape> circle_ptr = circleCreator.CreateShape(pointCenter, radius);
	m_shapes.push_back(circle_ptr);

	m_output << "Circle: P = " << circle_ptr->GetPerimeter() << ", S = " << circle_ptr->GetArea() << endl;
}

void ShapeHandler::GetTriangleData(istream& argsLine)
{
	string args;
	vector<string> points, p1, p2, p3;
	getline(argsLine, args);

	//убираем лишние пробелы и сплитим по оставшимся
	boost::algorithm::trim(args);
	boost::split(points, args, boost::algorithm::is_any_of(" "));

	//p1, p2, p3 - контейнеры для вершин
	boost::split(p1, points[0], boost::algorithm::is_any_of(","));
	boost::split(p2, points[1], boost::algorithm::is_any_of(","));
	boost::split(p3, points[2], boost::algorithm::is_any_of(","));

	//преобразуем в векторы из либы SFML
	sf::Vector2f vertex1 = { stof(p1[0]), stof(p1[1]) };
	sf::Vector2f vertex2 = { stof(p2[0]), stof(p2[1]) };
	sf::Vector2f vertex3 = { stof(p3[0]), stof(p3[1]) };

	//получаем экзепляр класса TriangleCreator
	auto& triCreator =TriangleCreator::GetInstance();

	//создаем экземпляр класса Circle с помощью TriangleCreator, заносим в массив фигур
	std::shared_ptr<IShape> triangle_ptr = triCreator.CreateShape(vertex1, vertex2, vertex3);
	m_shapes.push_back(triangle_ptr);

	m_output << "Triangle: P = " << triangle_ptr->GetPerimeter() << ", S = " << triangle_ptr->GetArea() << endl;
}

const std::vector<std::shared_ptr<IShape>>& ShapeHandler::GetShapesList()const
{
	return m_shapes;
}