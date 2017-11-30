/**
 * @file        
 * @brief       ##不能直接作用变量，实现动态的话还是需要一个字符串与函数指针的映射
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/
#include <iostream>
#include <string>

using namespace std;

#define DESC(VAL)  func_##VAL2##_func

void func_abc_func()
{
    cout << "abc" << endl;
}

void func_123_func()
{
    cout << "123" << endl;
}

void func_def_func()
{
    cout << "def" << endl;
}

int main()
{
    void (*funcs[3])();

    string intchar("test");

    funcs[0] = func_abc_func;
    funcs[1] = func_123_func;
    funcs[2] = func_def_func;

    string cmd;

    while (true)
    {
        getline(cin, cmd);
        if (cmd == "q")
            break;
        else
        {
            cout << string(DESC()) << endl;
        }
    }


    return 0;
}

