/*
 * @file        t1.cpp
 * @brief       使用嵌入汇编实现变量的自增
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <cstdio>

class Foo
{
public:
    void inc_fast()
    {
        __asm__ __volatile__(
            "lock incl %0"
            :"=m" (value)
            :"m" (value));
    }

    volatile int value;
};

int main() 
{
    Foo foo;

    foo.value = 10;

    printf("%d\n", foo.value);

    foo.inc_fast();

    printf("%d\n", foo.value);
}
