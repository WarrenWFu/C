#ifndef _CONDIMENTDECORATOR_H_
#define _CONDIMENTDECORATOR_H_	

#include "beverage.hpp"
class CondimentDecorator:public Beverage
{
public:
	virtual std::string getDescription() = 0;
};

#endif
