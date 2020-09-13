// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "CShapeHandler.h"

using namespace sf;
using namespace std;

//struct Args
//{
//    string input;
//    string output;
//};


int main(int argc, char* argv[])
{
    string input = argv[1];
    string output = argv[2];
    ifstream  inputFile;
    inputFile.open(input);
    ofstream outputFile;
    outputFile.open(output);

    CShapeHandler shapeHandler(inputFile, outputFile);

    while (!inputFile.eof() && !inputFile.fail())
    {
        shapeHandler.HandleCommand();
    }
    shapeHandler.DisplayShapes();
	return 0;
}