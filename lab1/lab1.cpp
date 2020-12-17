// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "CShapeHandler.h"

using namespace sf;
using namespace std;

int main(int argc, char* argv[])
{
    string input = argv[1];
    string output = argv[2];
    ifstream  inputFile;
    inputFile.open(input);
    ofstream outputFile;
    outputFile.open(output);

    auto& instance = CShapeHandler::GetInstance(inputFile, outputFile);

    while (!inputFile.eof() && !inputFile.fail())
    {
        instance.HandleCommand();
    }
    instance.DisplayShapes();
    return 0;
}