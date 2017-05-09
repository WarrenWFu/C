#include "studentoperation.h"

//注意这种嵌套类实例的定义方法
StudentOperation::StudentOperationRel 
	StudentOperation::studentOperationRel;
StudentOperation::StudentOperationRel::~StudentOperationRel()
{
	if(studentOperation)
	{
		delete studentOperation;	
	}
}

StudentOperation* StudentOperation::studentOperation;
StudentOperation* StudentOperation::getInstance()
{
	if(studentOperation == NULL)
	{
		studentOperation = new StudentOperation();
	}
	return studentOperation; 
}

int StudentOperation::readFile()
{
	return students.readFile();
}

int StudentOperation::writeFile()
{
	return students.writeFile();
}

int StudentOperation::listStudent(std::vector<std::string> *resultVector)
{
	int result = 0;
	std::vector<struct StudentForTran> studentForTranVector;
	std::vector<struct StudentForTran>::iterator SFTDIterator;

	result = students.listStudent(&studentForTranVector);
	if(result)
	{
		return -1;
	}
	
	for(SFTDIterator = studentForTranVector.begin(); 
			SFTDIterator < studentForTranVector.end(); SFTDIterator++)	
	{
		resultVector->push_back(studentInfoTranslate(*SFTDIterator));
	}

	return 0;
}

std::string StudentOperation::studentInfoTranslate(
		const struct StudentForTran& sftd)
{
	char resultCA[22+1];
	std::string resultString;
	memset(resultCA, 0x00, sizeof(resultCA));

	sprintf(resultCA, "%10d%10s%2d", sftd.id, sftd.name, sftd.gender);
	resultString.assign(resultCA);
	
	return resultString;
}

int StudentOperation::listOneStudent(int id, std::string *resultStringP)
{
	struct StudentForTran sftd;
	if(students.searchStudentForTran(id, &sftd))
	{
		return -1;	
	}

	*resultStringP = studentInfoTranslate(sftd);

	return 0;
}

int StudentOperation::addStudent(int id, const char* name, int gender)
{
	return students.addStudent(id, name, gender);
}
int StudentOperation::deleteStudent(int id)
{
	return students.deleteStudent(id);

}
int StudentOperation::modifyStudent(int id, const char* name)
{
	return students.modifyStudent(id, name);
}


