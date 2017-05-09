#ifndef STUDENT_OPERATION_H
#define STUDENT_OPERATION_H

#include <string>
#include <vector>
#include "studentfortran.h"
#include "students.h"

class StudentOperation
{
	public:
		int readFile();
		int writeFile();
		int listStudent(std::vector<std::string>*);   
		int listOneStudent(int, std::string*);
		int addStudent(int, const char*, int);    
		int deleteStudent(int); 
		int modifyStudent(int, const char*); 
		std::string studentInfoTranslate(const struct StudentForTran&);
		//std::string studentInfoTranslate(const StudentForTranDef&);
		static StudentOperation* getInstance();
		class StudentOperationRel
		{
			public:
				~StudentOperationRel();
				//{
				//}	
		};
	protected:
	private:
		static StudentOperation* studentOperation;
		static StudentOperationRel studentOperationRel;
		StudentOperation(){}
		Students students;
};
#endif
