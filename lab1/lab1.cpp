// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "CShapeHandler.h"

using namespace sf;
using namespace std;

const vector<shared_ptr<Shape>>& HandleFileAndGetShapes(CShapeHandler& handler, istream& file)
{
	while (!file.eof() && !file.fail())
	{
		handler.HandleCommand();
	}
	return handler.GetShapesList();
}

void DrawShapes(vector<shared_ptr<Shape>>& shapes)
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
			window.draw(**it);
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

    auto& instance = CShapeHandler::GetInstance(inputFile, outputFile);
	vector<shared_ptr<sf::Shape>> shapes = HandleFileAndGetShapes(instance, inputFile);
	DrawShapes(shapes);

    
    
}