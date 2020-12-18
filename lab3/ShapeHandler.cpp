#include "ShapeHandler.h"
#include <boost/algorithm/string.hpp>

#include "Creators.h"

using namespace std;
using namespace std::placeholders;


ShapeHandler::ShapeHandler(istream& input)
	: m_input(input)
	, m_actionMap({
	{ "Rectangle", bind(&ShapeHandler::GetRectangleData, this, _1) },
	{ "Circle", bind(&ShapeHandler::GetCircleData, this, _1) },
	{ "Triangle", bind(&ShapeHandler::GetTriangleData, this, _1) }
		})
{
}

ShapeHandler& ShapeHandler::GetInstance(std::istream& input)
{
	static ShapeHandler instance(input);
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

	//убираем лишние пробелы и сплитим по оставшимс€
	boost::algorithm::trim(args);
	boost::split(points, args, boost::algorithm::is_any_of(" "));

	//p1, p2 - контейнеры дл€ вершин
	boost::split(p1, points[0], boost::algorithm::is_any_of(","));
	boost::split(p2, points[1], boost::algorithm::is_any_of(","));

	//преобразуем в векторы из либы SFML
	sf::Vector2f leftTop = { stof(p1[0]), stof(p1[1]) };
	sf::Vector2f rightBottom = { stof(p2[0]), stof(p2[1]) };

	//получаем экзепл€р класса RectangleCreator
	auto& rectCreator = RectangleCreator::GetInstance();

	//создаем экзепл€р класса Rectangle с помощью RectangleCreator, заносим в массив фигур
	std::shared_ptr<IShape> rect_ptr = rectCreator.CreateShape(leftTop, rightBottom);
	m_shapes.push_back(rect_ptr);
}

void ShapeHandler::GetCircleData(istream& argsLine)
{
	string args;
	vector<string> params, center;
	getline(argsLine, args);

	//убираем лишние пробелы и сплитим по оставшимс€
	boost::algorithm::trim(args);
	boost::split(params, args, boost::algorithm::is_any_of(" "));

	//center - контейнер дл€ точки центра
	boost::split(center, params[0], boost::algorithm::is_any_of(","));

	float radius = stof(params[1]);

	//преобразуем в вектор из либы SFML
	sf::Vector2f pointCenter = { stof(center[0]), stof(center[1]) };

	//получаем экзепл€р класса CicleCreator
	auto& circleCreator = CircleCreator::GetInstance();

	//создаем экземпл€р класса Circle с помощью CircleCreator, заносим в массив фигур
	std::shared_ptr<IShape> circle_ptr = circleCreator.CreateShape(pointCenter, radius);
	m_shapes.push_back(circle_ptr);
}

void ShapeHandler::GetTriangleData(istream& argsLine)
{
	string args;
	vector<string> points, p1, p2, p3;
	getline(argsLine, args);

	//убираем лишние пробелы и сплитим по оставшимс€
	boost::algorithm::trim(args);
	boost::split(points, args, boost::algorithm::is_any_of(" "));

	//p1, p2, p3 - контейнеры дл€ вершин
	boost::split(p1, points[0], boost::algorithm::is_any_of(","));
	boost::split(p2, points[1], boost::algorithm::is_any_of(","));
	boost::split(p3, points[2], boost::algorithm::is_any_of(","));

	//преобразуем в векторы из либы SFML
	sf::Vector2f vertex1 = { stof(p1[0]), stof(p1[1]) };
	sf::Vector2f vertex2 = { stof(p2[0]), stof(p2[1]) };
	sf::Vector2f vertex3 = { stof(p3[0]), stof(p3[1]) };

	//получаем экзепл€р класса TriangleCreator
	auto& triCreator = TriangleCreator::GetInstance();

	//создаем экземпл€р класса Circle с помощью TriangleCreator, заносим в массив фигур
	std::shared_ptr<IShape> triangle_ptr = triCreator.CreateShape(vertex1, vertex2, vertex3);
	m_shapes.push_back(triangle_ptr);
}

const std::vector<std::shared_ptr<IShape>>& ShapeHandler::GetShapesList()const
{
	return m_shapes;
}
