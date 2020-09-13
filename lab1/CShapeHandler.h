#pragma once
#include "stdafx.h"

class CShapeHandler
{
	public:
		CShapeHandler(std::istream& input, std::ostream& output);
		void HandleCommand();
		void DisplayShapes()const;
	private:
		void GetRectangleData(std::istream& args);
		void GetCircleData(std::istream& args);
		void GetTriangleData(std::istream& args);
	private:
		using Handler = std::function<void(std::istream& args)>;
		using ActionMap = std::map<std::string, Handler>;

		std::istream& m_input;
		std::ostream& m_output;
		const ActionMap m_actionMap;
		std::vector<std::shared_ptr<Shape>> m_shapesList;
};