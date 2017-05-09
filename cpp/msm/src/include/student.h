#ifndef STUDENT_H
#define STUDENT_H

#include <unistd.h>
#include <cstring>

const int NAME_LENGTH = 10;

class Student
{
	public:
		Student(){}
		Student(int, const char*, int);
		~Student(){}
		int getId() const;
//这里为了防止通过返回的char*修改数组中的值，返回值必须为const
		//const char* getName const();
		char* getName();
		void setName(const char*);
		int getGender() const;
	protected:
	private:
		int id;
		char name[NAME_LENGTH+1];
		int gender;
};

#endif
