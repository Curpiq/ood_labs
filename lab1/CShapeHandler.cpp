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

CShapeHandler& CShapeHandler::GetInstance(std::istream& input, std::ostream& output)
{
	static CShapeHandler instance(input, output);
	return instance;
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

void CShapeHandler::GetRectangleData(istream& argsLine)
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

	//рассчитываем ширину и высоту для создания объекта класса RectangleShape из SFML
	float width = sqrt(pow((rightBottom.x - leftTop.x), 2));
	float height = sqrt(pow((leftTop.y - rightBottom.y), 2));

	//создаем фигуру SFML, устанавливаем позицию и заносим в массив фигур
	auto rect_ptr = make_shared<RectangleShape>(Vector2f(width, height));
	rect_ptr->setPosition(leftTop);
	m_shapes.push_back(rect_ptr);

	//декорируем обёрткой CRectangle
	CRectange rect = CRectange(move(*rect_ptr));

	//выводим в output информацию о площади и периметре
	m_output << "Rectangle: P = " << rect.GetPerimeter() << ", S = " << rect.GetArea() << endl;
}

void CShapeHandler::GetCircleData(istream& argsLine)
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
	Vector2f pointCenter = { stof(center[0]), stof(center[1]) };

	//создаем фигуру SFML, устанавливаем позицию заносим в массив фигур
	auto circle_ptr = make_shared<CircleShape>(radius);
	circle_ptr->setPosition(pointCenter);
	m_shapes.push_back(circle_ptr);

	//декорируем обёрткой CCircle
	CCircle circle = CCircle(move(*circle_ptr));

	//выводим в output информацию о площади и периметре
	m_output << "Circle: P = " << circle.GetPerimeter() << ", S = " << circle.GetArea() << endl;
}

void CShapeHandler::GetTriangleData(istream& argsLine)
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
	Vector2f vertex1 = { stof(p1[0]), stof(p1[1]) };
	Vector2f vertex2 = { stof(p2[0]), stof(p2[1]) };
	Vector2f vertex3 = { stof(p3[0]), stof(p3[1]) };

	//создаем фигуру SFML, устанавливаем позиции точек, заносим в массив
	auto tri_ptr = make_shared<ConvexShape>(3);
	tri_ptr->setPoint(0, vertex1);
	tri_ptr->setPoint(1, vertex2);
	tri_ptr->setPoint(2, vertex3);
	m_shapes.push_back(tri_ptr);

	//декорируем обёрткой CTriangle
	CTriangle triangle = CTriangle(move(*tri_ptr));

	//выводим в output информацию о площади и периметре
	m_output << "Triangle: P = " << triangle.GetPerimeter() << ", S = " << triangle.GetArea() << endl;
}

const std::vector<std::shared_ptr<sf::Shape>>& CShapeHandler::GetShapesList()const
{
	return m_shapes;
}


