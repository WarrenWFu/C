/**
 * @file        
 * @brief       单字节读取文件中内容并保存到字符串中
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//很奇怪如果每次分配1字节就会报错,2字节都不会
#define GRANULAR 1024

int main()
{
    char filename[15];
    char ch;
 
    printf("Enter the filename to be opened \n");
    scanf("%s", filename);
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    int iCnt = 1;
    char *pContent = (char *)calloc(GRANULAR * iCnt, sizeof(char));
    unsigned int iCounter = 0;
    ch = fgetc(fptr);
    while (ch != EOF)
    {
        pContent[iCounter++] = ch;
        if (iCounter == GRANULAR * iCnt)
        {
            ++iCnt;
            char *pTemp = (char *)realloc(pContent, GRANULAR * iCnt * sizeof(char));
            pContent = pTemp;
            memset(&pContent[GRANULAR * (iCnt-1)], 0x00, sizeof(GRANULAR));
        }
        ch = fgetc(fptr);
    }
    fclose(fptr);

    printf("%s", pContent);
    free(pContent);

    return 0;
}
