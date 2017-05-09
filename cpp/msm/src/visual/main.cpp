#include "main.h"

using namespace std;

namespace
{
	StudentOperation* studentOperation = StudentOperation::getInstance();
}
void listStudent();
void listOneStudent();
void deleteStudent();
void modifyStudent();

int main()
{
#if 1
	//将文件中的信息装入内存容器中
	int result = 0;

	result = studentOperation->readFile();
	if(result < 0)
	{
		cout << "open student file fail" << endl;
		return -1;
	}

	string commandStr;
	bool flag = false;

	cout << "---------------Welcome to MSM system---------------" << endl;
	cout << "please input you choice" << endl;
	cout << "\t1.list the students" << endl;
	cout << "\t2.list one student" << endl;
	cout << "\t3.add student" << endl;
	cout << "\t4.delete student" << endl;
	cout << "\t5.modify the student" << endl;
	cout << "\t6.quit" << endl;

	flag= true;
	while(flag)
	{
		getline(cin, commandStr);	
		switch(commandStr[0])
		{
			case '1':
				listStudent();
				break;
			case '2':
				listOneStudent();
				break;
			case '3':
				studentOperation->addStudent(1, "abc", 1);
				break;
			case '4':
				deleteStudent();
				break;
			case '5':
				modifyStudent();
				break;
			case '6':
				flag = false;
				result = 0;
				if(studentOperation->writeFile())
				{
					cout << "write file failed" << endl;	
				}
				break;
			default:
				cout << "bad command" << endl;
				break;
		}
	}	

#endif
	return 0;	

}

void listStudent()
{
	vector<string> studentInfo;
	vector<string>::iterator iterator;

	if(!studentInfo.empty())
	{
		studentInfo.clear();
	}
	if(studentOperation->listStudent(&studentInfo))
		cout << "no record" << endl;
	else
	{
		for(iterator = studentInfo.begin(); 
				iterator < studentInfo.end(); iterator++)
		{
			cout << (*iterator)	<< endl;
		}
	}
}

void listOneStudent()
{
	string idString;
	string resultString;
	int flag = 0;

	while(true)
	{
		flag = 0;
		cout << "input the id for list(q to quit):" << endl;
		getline(cin, idString);
		if(idString[0] == 'q')
			break;

		if((int)idString.size() > 10)
		{
			cout << "too long" << endl;
			continue;
		}
		else 
		{
			for(int i = 0; i < (int)idString.size(); i++)	
			{
				if(!isdigit(idString[i]))	
				{
					cout << "please input digit" << endl;
					flag = 1;
					break;
				}
			}
			if(flag != 0)
				continue;
		}

		if(studentOperation->listOneStudent(
					atoi(idString.c_str()), &resultString))
		{
			cout << "no record" << endl;	
			continue;
		}

		cout << resultString << endl;
	}

}

void deleteStudent()
{
	string idString;
	int flag = 0;

	while(true)
	{
		flag = 0;
		cout << "input the id for delete(q to quit):" << endl;
		getline(cin, idString);
		if(idString[0] == 'q')
			break;

		if((int)idString.size() > 10)
		{
			cout << "too long" << endl;
			continue;
		}
		else 
		{
			for(int i = 0; i < (int)idString.size(); i++)	
			{
				if(!isdigit(idString[i]))	
				{
					cout << "please input digit" << endl;
					flag = 1;
					break;
				}
			}
			if(flag != 0)
				continue;
		}

		if(studentOperation->deleteStudent(atoi(idString.c_str())))
		{
			cout << "no record" << endl;	
			continue;
		}

		cout << "delete the record of id[" << idString
		   	<<  "] complete" << endl;
	}

}
void modifyStudent()
{
	string idString;
	string nameString;
	int flag = 0;

	while(true)
	{
		flag = 0;
		cout << "input the id for modify(q to quit):" << endl;
		getline(cin, idString);
		if(idString[0] == 'q')
			break;

		if((int)idString.size() > 10)
		{
			cout << "too long" << endl;
			continue;
		}
		else 
		{
			for(int i = 0; i < (int)idString.size(); i++)	
			{
				if(!isdigit(idString[i]))	
				{
					cout << "please input digit" << endl;
					flag = 1;
					break;
				}
			}
			if(flag != 0)
				continue;
		}
		cout << "input the new name(q to quit):" << endl;
		getline(cin, nameString);
		if((int)nameString.size() > 10)
		{
			cout << "new name is too long" << endl;	
			continue;
		}

		if(studentOperation->modifyStudent(
					atoi(idString.c_str()), nameString.c_str()))
		{
			cout << "no record" << endl;
			continue;
		}
		cout << "modify complete" << endl;
	}


}
