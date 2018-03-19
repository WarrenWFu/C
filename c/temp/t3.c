/**
 * @file        
 * @brief       使用GNU扩展的关键字typeof自动推到出变量类型，类似C++14的auto
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <stdio.h>

int main()
{
    char *s1 = "123";
    typeof(s1) p1 = s1;

    printf("%s\n", p1);

    return 0;
}
