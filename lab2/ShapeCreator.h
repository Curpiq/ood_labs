#pragma once
#include "IShape.h"
#include <memory>
class ShapeCreator
{
public:
	virtual ~ShapeCreator() {};
	void CreateShape()const
	{
		//auto& shape = ;
	}
protected:
	virtual std::shared_ptr<IShape> FactoryMethod()const = 0;

};