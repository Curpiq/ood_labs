#include "stdfx.h"
#include "ShapeCreators.h"
#include "ShapeHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
	string input = argv[1];
	string output = argv[2];
	ifstream  inputFile;
	inputFile.open(input);
	ofstream outputFile;
	outputFile.open(output);

	auto& instance = ShapeHandler::GetInstance(inputFile, outputFile);

	while (!inputFile.eof() && !inputFile.fail())
	{
		instance.HandleCommand();
	}
	instance.DisplayShapes();
	return 0;
}
