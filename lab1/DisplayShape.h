#pragma once
#include "SFML/Graphics.hpp"
#include "IShape.h"

//class DisplayShape
//{
//	public:
//		void Display(IShape const& shape, std::string const& shapeName)
//		{
//			RenderWindow window(VideoMode(100, 100), "Shape");
//			while (window.isOpen())
//			{
//				// ������������ ������� ������� � �����
//				Event event;
//				while (window.pollEvent(event))
//				{
//					// ������������ ����� �� �������� � ����� ������� ����?
//					if (event.type == Event::Closed)
//						// ����� ��������� ���
//						window.close();
//				}
//				//window.draw();
//				// ��������� ����	
//				window.display();
//			}
//		}
//		private Shape m_shape;
//};

template <typename T>
class DisplayShape
{
	public:
		void Display()
};