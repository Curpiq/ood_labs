// lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "StreamOutputVisitor.h"
#include "ShapeHandler.h"

using namespace std;

const vector<shared_ptr<IShape>>& HandleFileAndGetShapes(ShapeHandler& handler, istream& file)
{
	while (!file.eof() && !file.fail())
	{
		handler.HandleCommand();
	}
	return handler.GetShapesList();
}

void WriteShapesInfo(ostream& output, vector<shared_ptr<IShape>>& shapes)
{
	StreamOutputVisitor visitor(output);
	for (auto it = shapes.begin(); it != shapes.end(); it++)
	{
		(*it)->Accept(visitor);
	}
}

void DrawShapes(vector<shared_ptr<IShape>>& shapes)
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

int main(int argc, char* argv[])
{
	string input = argv[1];
	string output = argv[2];
	ifstream  inputFile;
	inputFile.open(input);
	ofstream outputFile;
	outputFile.open(output);

	auto& instance = ShapeHandler::GetInstance(inputFile);
	vector<shared_ptr<IShape>> shapes = HandleFileAndGetShapes(instance, inputFile);

	WriteShapesInfo(outputFile, shapes);

	DrawShapes(shapes);	
}
