#pragma once
#include "stdfx.h"
#include "ShapeHandler.h"

using namespace std;

class Application
{
private:
	string input;
	string output;
	ifstream inputFile;
	ofstream outputFile;
public:
	Application(char* arg1, char* arg2)
		:input(arg1)
		, output(arg2)
	{
		OpenFiles(input, output);
		StreamOutputVisitor visitor(outputFile);
		HandleInputFile(visitor);
		std::vector<std::shared_ptr<sf::Shape>> shapes = GetShapesList(visitor);
		DrawShapes(shapes);
	}

	void OpenFiles(const string& input, string& output)
	{
		inputFile.open(input);
		outputFile.open(output);
	}

	void HandleInputFile(StreamOutputVisitor& visitor)
	{
		auto& shapeHandler = ShapeHandler::GetInstance(inputFile, visitor);
		while (!inputFile.eof() && !inputFile.fail())
		{
			shapeHandler.HandleCommand();
		}
	}

	std::vector<std::shared_ptr<sf::Shape>> GetShapesList(StreamOutputVisitor& visitor)
	{
		auto& shapeHandler = ShapeHandler::GetInstance(inputFile, visitor);
		return shapeHandler.GetShapesList();
	}

	void DrawShapes(std::vector<std::shared_ptr<sf::Shape>>& shapes)
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
};

