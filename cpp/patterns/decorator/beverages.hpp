#ifndef _BEVERAGE_HPP_
#define _BEVERAGE_HPP_

#include "mycommon.hpp"
class Beverage
{
public:
	Beverage():description("Unknown Beverage"){}
	std::string getDescription()
	{
		return description;	
	}
	virtual double cost() = 0;
protected:
	std::string description;
private:
};


class Espresso: public Beverage
{
public:
	Espresso():description("Espresso"){}
	double cost() { return 1.99; }
protected:
private:
};


class HouseBlend: public Beverage
{
public:
	Espresso():description("HouseBlend"){}
	double cost() { return .89; }
protected:
private:
};


#endif
