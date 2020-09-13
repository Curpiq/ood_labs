#include "CShapeHandler.h"
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace std::placeholders;

CShapeHandler::CShapeHandler(istream& input, ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
				{ "Rectangle", bind(&CShapeHandler::GetRectangleData, this, _1) },
				{ "Circle", bind(&CShapeHandler::GetCircleData, this, _1) },
				{ "Triangle", bind(&CShapeHandler::GetTriangleData, this, _1) }
		})
{
}
void CShapeHandler::HandleCommand()
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

void CShapeHandler::GetRectangleData(istream& args)
{
	string command;
	vector<string> params, p1, p2;
	getline(args, command);

	boost::algorithm::trim(command);
	boost::split(params, command, boost::algorithm::is_any_of(" "));

	boost::split(p1, params[0], boost::algorithm::is_any_of(","));
	boost::split(p2, params[1], boost::algorithm::is_any_of(","));

	Vector2f point1 = { stof(p1[0]), stof(p1[1]) };
	Vector2f point2 = { stof(p2[0]), stof(p2[1]) };

	float width = sqrt(pow((point2.x - point1.x), 2));
	float height = sqrt(pow((point2.y - point1.y), 2));

	auto shape_ptr = make_shared<RectangleShape>(Vector2f(width, height));
	m_shapesList.push_back(shape_ptr);

	CRectange rectangle(*shape_ptr);
	m_output << "Rectangle: P = " << rectangle.GetPerimeter() << ", S = " << rectangle.GetArea() << endl;
}

void CShapeHandler::GetCircleData(istream& args)
{
	string command;
	vector<string> params, center;
	getline(args, command);
	boost::algorithm::trim(command);

	boost::split(params, command, boost::algorithm::is_any_of(" "));
	boost::split(center, params[0], boost::algorithm::is_any_of(","));
	Vector2f pointCenter = { stof(center[0]), stof(center[1]) };
	float radius = stof(params[1]);

	auto shape_ptr = make_shared<CircleShape>(radius);
	shape_ptr->setPosition(pointCenter.x, pointCenter.y);
	m_shapesList.push_back(shape_ptr);

	CCircle circle(*shape_ptr);
	m_output << "Circle: P = " << circle.GetPerimeter() << ", S = " << circle.GetArea() << endl;
}

void CShapeHandler::GetTriangleData(istream& args)
{
	string command;
	vector<string> params, p1, p2, p3;
	getline(args, command);

	boost::algorithm::trim(command);
	boost::split(params, command, boost::algorithm::is_any_of(" "));

	boost::split(p1, params[0], boost::algorithm::is_any_of(","));
	boost::split(p2, params[1], boost::algorithm::is_any_of(","));
	boost::split(p3, params[2], boost::algorithm::is_any_of(","));

	Vector2f vertex1 = { stof(p1[0]), stof(p1[1]) };
	Vector2f vertex2 = { stof(p2[0]), stof(p2[1]) };
	Vector2f vertex3 = { stof(p3[0]), stof(p3[1]) };

	auto shape_ptr = make_shared<ConvexShape>(3);
	shape_ptr->setPoint(0, vertex1);
	shape_ptr->setPoint(1, vertex2);
	shape_ptr->setPoint(2, vertex3);
	m_shapesList.push_back(shape_ptr);

	CTriangle triangle(*shape_ptr);
	m_output << "Triangle: P = " << triangle.GetPerimeter() << ", S = " << triangle.GetArea() << endl;
}

void CShapeHandler::DisplayShapes()const
{
	for (auto it = m_shapesList.begin(); it != m_shapesList.end(); it++)
	{
		RenderWindow window(sf::VideoMode(200, 200), "Shape");
		(*it)->setFillColor(Color::Cyan);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			};
			window.draw(**it);
			window.display();
		}
	}
}
