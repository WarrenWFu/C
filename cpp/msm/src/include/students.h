#ifndef STUDENTS_H
#define STUDENTS_H
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <exception>
#include <unistd.h>
#include <iostream>
#include "student.h"
#include "studentfortran.h"

//enum DeleteType
//{
//	Id,Name
//};

class Students
{
	public:
		Students();
		~Students();
		int readFile();
		int writeFile();
		int listStudent(std::vector<struct StudentForTran>*);
		int addStudent(int, const char*, int);
		int deleteStudent(int);
		int modifyStudent(int, const char*);
		int searchStudentForTran(int, struct StudentForTran*);
	protected:
	private:
		Student* searchStudent(int);
		std::vector<Student> studentVector;
		char *filePath;
};
#endif
