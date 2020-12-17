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

ShapeHandler& ShapeHandler::GetInstance(std::istream& input, std::ostream& output)
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

	//сплитим по запятой, создаем векторы p1, p2 для точек
	boost::split(p1, points[0], boost::algorithm::is_any_of(","));
	boost::split(p2, points[1], boost::algorithm::is_any_of(","));

	//приводим к векторам из SFML
	sf::Vector2f leftTop = { stof(p1[0]), stof(p1[1]) };
	sf::Vector2f rightBottom = { stof(p2[0]), stof(p2[1]) };

	//рассчитываем ширину и высоту для создания объекта класса RectangleShape из SFML
	float width = sqrt(pow((rightBottom.x - leftTop.x), 2));
	float height = sqrt(pow((leftTop.y - rightBottom.y), 2));

	//получаем экзепляр класса RectangleCreator
	auto& rectCreator = RectangleCreator::GetInstance();

	//создаем фигуру SFML, устанавливаем позицию
	sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(width, height));
	rectangle.setPosition(leftTop);


	//создаем экзепляр класса Rectangle с помощью RectangleCreator, заносим в массив фигур
	std::shared_ptr<IShape> rect_ptr = rectCreator.CreateShape(std::move(rectangle));
	shapes.push_back(rect_ptr);

	//выводим в output информацию о площади и периметре
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

	//сплитим по запятой, создаем вектор center для точки центра, заводим переменную радиуса
	boost::split(center, params[0], boost::algorithm::is_any_of(","));
	float radius = stof(params[1]);

	//приводим к вектору SFML
	sf::Vector2f pointCenter = { stof(center[0]), stof(center[1]) };

	//создаем фигуру SFML, устанавливаем позицию
	sf::CircleShape circle = sf::CircleShape(radius);
	circle.setPosition(pointCenter);

	//получаем экзепляр класса CicleCreator
	auto& circleCreator = CircleCreator::GetInstance();

	//создаем экземпляр класса Circle с помощью CircleCreator, заносим в массив фигур
	std::shared_ptr<IShape> circle_ptr = circleCreator.CreateShape(std::move(circle));
	shapes.push_back(circle_ptr);

	//выводим в output информацию о площади и периметре
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

	//сплитим по запятой, создаем векторы p1, p2, p3 для точек
	boost::split(p1, points[0], boost::algorithm::is_any_of(","));
	boost::split(p2, points[1], boost::algorithm::is_any_of(","));
	boost::split(p3, points[2], boost::algorithm::is_any_of(","));

	//приводим к векторам из SFML
	sf::Vector2f vertex1 = { stof(p1[0]), stof(p1[1]) };
	sf::Vector2f vertex2 = { stof(p2[0]), stof(p2[1]) };
	sf::Vector2f vertex3 = { stof(p3[0]), stof(p3[1]) };

	//создаем фигуру SFML, устанавливаем позиции точек
	sf::ConvexShape triangle = sf::ConvexShape(3);
	triangle.setPoint(0, vertex1);
	triangle.setPoint(1, vertex2);
	triangle.setPoint(2, vertex3);

	//получаем экзепляр класса TriangleCreator
	auto& triCreator =TriangleCreator::GetInstance();

	//создаем экземпляр класса Circle с помощью TriangleCreator, заносим в массив фигур
	std::shared_ptr<IShape> triangle_ptr = triCreator.CreateShape(std::move(triangle));
	shapes.push_back(triangle_ptr);

	//выводим в output информацию о площади и периметре
	m_output << "Circle: P = " << triangle_ptr->GetPerimeter() << ", S = " << triangle_ptr->GetArea() << endl;
}

void ShapeHandler::DisplayShapes()const
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Shapes");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		};
		for (auto it = shapes.begin(); it != shapes.end(); it++)
		{
			window.draw((*it)->GetSFShape());
		}
		window.display();
	}
}