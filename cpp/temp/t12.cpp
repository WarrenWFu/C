/**
 * @file        
 * @brief       使用void*可以实现存放任意变量的数组和一个简单的Object模拟
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

class Object{
public:
    void * m_p;

    Object() {m_p = NULL;}
    virtual ~Object() {}

    template <class Type>
        void operator = (Type p)
        {
            this->m_p= (void*)p;
        }

//    template <>
//        void operator = <string>(string Value){
//            this->Value = (void*)Value.c_str();
//        }
//
//    template <class Type>
//        bool operator ==  (Type Value2){
//            return (int)(void*)Value2==(int)(void*)this->Value;
//        }
//
//    template<>
//        bool operator == <Object> (Object Value2){
//            return Value2.Value==this->Value;
//        }
//
//    template <class ReturnType>
//        ReturnType Get(){
//            return (ReturnType)this->Value;
//        }
//
//    template <>
//        string Get(){
//            string str = (const char*)this->Value;
//            return str;
//        }
//
//    template <>
//        void* Get(){
//
//            return this->Value;
//        }
//
//    void Print(){
//        cout << (signed)this->Value << endl;
//    }
};

int main()
{
//    //使用void*实现数据中放各种元素是可行的,但是操作比较麻烦总是要强转
//    void* iA[5];
//    int i = 2;
//    iA[0] = &i;
//    cout << *(int *)(iA[0]) << endl;

    int i = 2;
    Object objs[5];
    objs[0] = &i;
    cout << *(int *)(objs[0].m_p) << endl;

    string s = "123";
    objs[1] = &s;
    cout << *(string *)(objs[1].m_p) << endl;


    return 0;
}

