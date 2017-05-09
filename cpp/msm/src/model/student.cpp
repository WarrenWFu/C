#include "student.h"

Student::Student(int id, const char *name, int gender)
{
	this->id = id;
	strcpy(this->name, name);
	this->gender = gender;
}

int Student::getId() const
{
	return id;
}

char* Student::getName()
{
	return name;
}

void Student::setName(const char* newName)
{
	memset(name, '\0', NAME_LENGTH+1);
	strcpy(name,newName);
}

int Student::getGender() const
{
	return gender;
}
