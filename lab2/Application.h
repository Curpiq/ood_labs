#pragma once
#pragma once
#include "stdfx.h"
#include "ShapeHandler.h"
class Application
{
private:
	std::string input;
	std::string output;
	std::ifstream inputFile;
	std::ofstream outputFile;
public:
	Application(char* arg1, char* arg2)
		:input(arg1)
		, output(arg2)
	{
		{
			OpenFiles(input, output);
			HandleInputFile();
			std::vector<std::shared_ptr<sf::Shape>> shapes = GetShapesList();
			DrawShapes(shapes);
		}
	}

	void OpenFiles(std::string const& input, std::string const& output)
	{
		inputFile.open(input);
		outputFile.open(output);
	}

	void HandleInputFile()
	{
		auto& shapeHandler = ShapeHandler::GetInstance(inputFile, outputFile);
		while (!inputFile.eof() && !inputFile.fail())
		{
			shapeHandler.HandleCommand();
		}
	}
	std::vector<std::shared_ptr<sf::Shape>> GetShapesList()
	{
		auto& shapeHandler = ShapeHandler::GetInstance(inputFile, outputFile);
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