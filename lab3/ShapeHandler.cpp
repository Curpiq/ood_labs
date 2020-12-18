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

	//������� ������ ������� � ������� �� ����������
	boost::algorithm::trim(args);
	boost::split(points, args, boost::algorithm::is_any_of(" "));

	//p1, p2 - ���������� ��� ������
	boost::split(p1, points[0], boost::algorithm::is_any_of(","));
	boost::split(p2, points[1], boost::algorithm::is_any_of(","));

	//����������� � ������� �� ���� SFML
	sf::Vector2f leftTop = { stof(p1[0]), stof(p1[1]) };
	sf::Vector2f rightBottom = { stof(p2[0]), stof(p2[1]) };

	//�������� �������� ������ RectangleCreator
	auto& rectCreator = RectangleCreator::GetInstance();

	//������� �������� ������ Rectangle � ������� RectangleCreator, ������� � ������ �����
	std::shared_ptr<IShape> rect_ptr = rectCreator.CreateShape(leftTop, rightBottom);
	m_shapes.push_back(rect_ptr);
}

void ShapeHandler::GetCircleData(istream& argsLine)
{
	string args;
	vector<string> params, center;
	getline(argsLine, args);

	//������� ������ ������� � ������� �� ����������
	boost::algorithm::trim(args);
	boost::split(params, args, boost::algorithm::is_any_of(" "));

	//center - ��������� ��� ����� ������
	boost::split(center, params[0], boost::algorithm::is_any_of(","));

	float radius = stof(params[1]);

	//����������� � ������ �� ���� SFML
	sf::Vector2f pointCenter = { stof(center[0]), stof(center[1]) };

	//�������� �������� ������ CicleCreator
	auto& circleCreator = CircleCreator::GetInstance();

	//������� ��������� ������ Circle � ������� CircleCreator, ������� � ������ �����
	std::shared_ptr<IShape> circle_ptr = circleCreator.CreateShape(pointCenter, radius);
	m_shapes.push_back(circle_ptr);
}

void ShapeHandler::GetTriangleData(istream& argsLine)
{
	string args;
	vector<string> points, p1, p2, p3;
	getline(argsLine, args);

	//������� ������ ������� � ������� �� ����������
	boost::algorithm::trim(args);
	boost::split(points, args, boost::algorithm::is_any_of(" "));

	//p1, p2, p3 - ���������� ��� ������
	boost::split(p1, points[0], boost::algorithm::is_any_of(","));
	boost::split(p2, points[1], boost::algorithm::is_any_of(","));
	boost::split(p3, points[2], boost::algorithm::is_any_of(","));

	//����������� � ������� �� ���� SFML
	sf::Vector2f vertex1 = { stof(p1[0]), stof(p1[1]) };
	sf::Vector2f vertex2 = { stof(p2[0]), stof(p2[1]) };
	sf::Vector2f vertex3 = { stof(p3[0]), stof(p3[1]) };

	//�������� �������� ������ TriangleCreator
	auto& triCreator = TriangleCreator::GetInstance();

	//������� ��������� ������ Circle � ������� TriangleCreator, ������� � ������ �����
	std::shared_ptr<IShape> triangle_ptr = triCreator.CreateShape(vertex1, vertex2, vertex3);
	m_shapes.push_back(triangle_ptr);
}

const std::vector<std::shared_ptr<IShape>>& ShapeHandler::GetShapesList()const
{
	return m_shapes;
}
