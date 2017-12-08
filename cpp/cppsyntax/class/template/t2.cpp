/**
 * @file        
 * @brief       判断一个变量是否为指针
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
 */

#include <iostream>
#include <string>

using namespace std;

template<typename T>
class aux
{
public:
    enum{val = 0};
};

template<typename T>
class aux<T *>
{
public:
    enum{val = 1};
};

template<typename T>
bool IsPtr(const T &)
{
    return aux<T>::val;
}

int func(int)
{
    return 0;
}

int main()
{
    int a[2] = {0};
    int i = 0;
    int *p = 0;

    const int *cp = 0;
    int *const pc = 0;
    const int *const cpc = 0;

    string s;
    std::is_pointer
    cout<<IsPtr(a)<<endl;//数组名不是指针 
    cout<<IsPtr(func)<<endl;//函数名不是指针，但是&func是指针
    cout<<IsPtr(s)<<endl;//string不是指针
    cout<<IsPtr(i)<<endl;
    cout<<IsPtr(p)<<endl;
    cout<<IsPtr(cp)<<endl;
    cout<<IsPtr(pc)<<endl;
    cout<<IsPtr(cpc)<<endl;

    return 0;
}

