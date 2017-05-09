#ifndef _CONDIMENTDECORATOR_H_
#define _CONDIMENTDECORATOR_H_	

#include "beverage.hpp"

class CondimentDecorator:public Beverage
{
public:
	virtual std::string getDescription() = 0;
};

class Mocha:public CondimentDecorator
{
public:
	Mocha(Beverage value):beverage(value){}
	std::string getDescription()
	{
		return beverage->getDescription() + ", Mocha";	
	}
	public double cost()
	{
		return .20 + beverage->cost();	
	}
private:
	Beverage *beverage;
};

#endif
