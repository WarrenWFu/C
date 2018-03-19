/**
 * @file        
 * @brief       一个简单的判断字节序代码。
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <stdio.h>

int main()
{

    int n = 0x1234;
    char *p = (char *)&n;

    if (p[0] == 0x12)
        printf("大端\n");
    else if (p[0] == 0x34)
        printf("小端\n");
    else
        printf("字节序不明\n");

    return 0;
}

