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
//				// Обрабатываем очередь событий в цикле
//				Event event;
//				while (window.pollEvent(event))
//				{
//					// Пользователь нажал на «крестик» и хочет закрыть окно?
//					if (event.type == Event::Closed)
//						// Тогда закрываем его
//						window.close();
//				}
//				//window.draw();
//				// Отрисовка окна	
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