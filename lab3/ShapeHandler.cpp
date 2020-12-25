#include <boost/algorithm/string.hpp>
#include "ShapeHandler.h"

using namespace std;
using namespace std::placeholders;

ShapeHandler::ShapeHandler(istream& input, StreamOutputVisitor& visitor)
	: m_input(input)
	, m_visitor(visitor)
	, m_actionMap({ { "Rectangle", bind(&ShapeHandler::GetRectangleData, this, _1)} ,
		{ "Circle", bind(&ShapeHandler::GetCircleData, this, _1) },
		{ "Triangle", bind(&ShapeHandler::GetTriangleData, this, _1) }
		})
{
}

ShapeHandler& ShapeHandler::GetInstance(istream& input, StreamOutputVisitor& visitor)
{
	static ShapeHandler instance(input, visitor);
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

	//???????????? ?????? ?????
	boost::algorithm::trim(args);
	boost::split(points, args, boost::algorithm::is_any_of(" "));

	//p1, p2 - ????? ?? ???
	boost::split(p1, points[0], boost::algorithm::is_any_of(","));
	boost::split(p2, points[1], boost::algorithm::is_any_of(","));

	
	sf::Vector2f leftTop = { stof(p1[0]), stof(p1[1]) };
	sf::Vector2f rightBottom = { stof(p2[0]), stof(p2[1]) };


	float width = sqrt(pow((rightBottom.x - leftTop.x), 2));
	float height = sqrt(pow((leftTop.y - rightBottom.y), 2));

	auto rect_ptr = make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
	rect_ptr->setPosition(leftTop);
	m_shapes.push_back(rect_ptr);
	auto& rectCreator = RectangleCreator::GetInstance();

	auto rectangle = rectCreator.CreateShape(*rect_ptr);
	rectangle->PrintInfo(m_visitor);
}

void ShapeHandler::GetCircleData(istream& argsLine)
{
	string args;
	vector<string> params, center;
	getline(argsLine, args);


	boost::algorithm::trim(args);
	boost::split(params, args, boost::algorithm::is_any_of(" "));

	boost::split(center, params[0], boost::algorithm::is_any_of(","));

	float radius = stof(params[1]);

	sf::Vector2f pointCenter = { stof(center[0]), stof(center[1]) };

	
	auto circle_ptr = make_shared<sf::CircleShape>(radius);
	circle_ptr->setPosition(pointCenter);
	m_shapes.push_back(circle_ptr);

	
	auto& circleCreator = CircleCreator::GetInstance();

	auto circle = circleCreator.CreateShape(*circle_ptr);

	
	circle->PrintInfo(m_visitor);
}

void ShapeHandler::GetTriangleData(istream& argsLine)
{
	string args;
	vector<string> points, p1, p2, p3;
	getline(argsLine, args);

	boost::algorithm::trim(args);
	boost::split(points, args, boost::algorithm::is_any_of(" "));

	
	boost::split(p1, points[0], boost::algorithm::is_any_of(","));
	boost::split(p2, points[1], boost::algorithm::is_any_of(","));
	boost::split(p3, points[2], boost::algorithm::is_any_of(","));

	
	sf::Vector2f vertex1 = { stof(p1[0]), stof(p1[1]) };
	sf::Vector2f vertex2 = { stof(p2[0]), stof(p2[1]) };
	sf::Vector2f vertex3 = { stof(p3[0]), stof(p3[1]) };

	
	auto tri_ptr = std::make_shared<sf::ConvexShape>(3);
	tri_ptr->setPoint(0, vertex1);
	tri_ptr->setPoint(1, vertex2);
	tri_ptr->setPoint(2, vertex3);
	m_shapes.push_back(tri_ptr);

	
	auto& triangleCreator = TriangleCreator::GetInstance();

	auto triangle = triangleCreator.CreateShape(*tri_ptr);

	
	triangle->PrintInfo(m_visitor);
}
const std::vector<std::shared_ptr<sf::Shape>>& ShapeHandler::GetShapesList()const
{
	return m_shapes;
}