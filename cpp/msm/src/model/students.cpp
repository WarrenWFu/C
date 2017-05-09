#include "students.h"

Students::Students()
{
	filePath = NULL;
}

Students::~Students()
{
}

int Students::readFile()
{
	//get student data from file
	Student student;
	int result = 0;
	FILE *fp = NULL;

	filePath = getenv("STUDENTFILE");
	if(filePath == NULL)
	{
		return -1;
	}

	if(access(filePath, F_OK | R_OK | W_OK) != 0)
	{
		//文件不存在或者权限不能读写则创建并以读写方式打开
		fp = fopen(filePath, "w+");	
	}
	//文件存在则以读写方式打开
	else
	{
		fp = fopen(filePath, "r");
	
	}
	if(fp == NULL)
	{
		return -1;
	}
	result = 0;
	do
	{
		result = fread(&student, sizeof(Student), 1, fp);
		if(result != 1)
		{
			break;	
		}
		studentVector.push_back(student);
	}while(true);

	fclose(fp);

//c++的文件流处理速度慢，不如直接使用c的流函数
#if 0
	std::fstream studentFile;
	if(access(filePath, F_OK | R_OK | W_OK) != 0)
	{
		//直接创建文件
		studentFile.open(filePath, std::fstream::out | std::fstream::binary);
	}
	else
	{
		studentFile.open(filePath, 
				std::fstream::in| std::fstream::out | std::fstream::binary);
	}

	if(studentFile.fail())
	{
		throw std::exception();	
	}

	//	>>每次读取一行
	studentFile >> test;
	studentFile.close();

#endif


	return 0;

}
int Students::writeFile()
{
	int result = 0;
	FILE *fp = NULL;

	//先备份原文件,判断三个值确保调用成功
	result = system("mv $STUDENTFILE $STUDENTFILE.bak");
	if(-1 == result)
	{
		return -1;
	}
	else
	{
		if( !WIFEXITED(result) || (0 != WEXITSTATUS(result)))	
		{
			return -1;	
		}
	}

	fp = NULL;
	//以读写方式创建文件
	fp = fopen(filePath, "w+");
	if(!fp)
	{
		return -1;
	}

	//判断内存容器是否为空
	if(studentVector.empty())
	{
		fclose(fp);	
		return 0;
	}
	result = 0;	
	std::vector<Student>::iterator iterator = studentVector.begin();
	for(; iterator < studentVector.end(); 
			iterator++)
	{
		result = fwrite((Student *)&(*iterator), sizeof(Student), 1, fp);
		if(result != 1)
		{
			return -1;	
		}
	}

	fclose(fp);

	return 0;

}

int Students::listStudent(std::vector<struct StudentForTran> *listVectorP)
{
	std::vector<Student>::iterator iterator;
	struct StudentForTran studentForTran;

	memset(&studentForTran, 0x00, sizeof(struct StudentForTran));
	
	if(studentVector.empty())
	{
		return -1;
	}

	for(iterator = studentVector.begin(); iterator < studentVector.end(); 
			iterator++)
	{
		memset(&studentForTran, 0x00, sizeof(struct StudentForTran));

		studentForTran.id = (*iterator).getId();
		strncpy(studentForTran.name, (*iterator).getName(),
			   	strlen((*iterator).getName()));
		studentForTran.gender = (*iterator).getGender();

		listVectorP->push_back(studentForTran);
	}

	return 0;
}

int Students::addStudent(int id, const char* name, int gender)
{
	Student student(id, name, gender); 
	studentVector.push_back(student);
	return 0;
}

int Students::deleteStudent(int id)
{
	std::vector<Student>::iterator iterator;

	if(studentVector.empty())
	{
		return -1;
	}

	for(iterator = studentVector.begin(); iterator < studentVector.end(); 
			iterator++)
	{
		if((*iterator).getId() == id)	
		{
			studentVector.erase(iterator);
			return 0;
		}
	}

	return -1;
}

int Students::modifyStudent(int id, const char *newName)
{
	Student *studentP = NULL;
	studentP = searchStudent(id);
	if(NULL == studentP)
	{
		return -1;
	}
	else
	{
		studentP->setName(newName);
		return 0;
	}
}

Student* Students::searchStudent(int id)
{
	std::vector<Student>::iterator iterator;
	
	if(studentVector.empty())
	{
		return NULL;
	}

	for(iterator = studentVector.begin(); iterator < studentVector.end(); 
			iterator++)
	{
		if((*iterator).getId() == id)	
		{
			return &(*iterator);
		}
	}

	return NULL;
}
int Students::searchStudentForTran(int id, struct StudentForTran* sftd)
{
	Student *studentP = NULL;
	studentP = searchStudent(id);

	if(NULL == studentP)
	{
		return -1;	
	}
	else
	{
		sftd->id = studentP->getId();
		strcpy(sftd->name, studentP->getName());
		sftd->gender = studentP->getGender();
		return 0;
	}
}

