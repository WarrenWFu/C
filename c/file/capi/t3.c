/**
 * @file        
 * @brief       删除文件中指定的行
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
 */
#include <stdio.h>
 
int main()
{
    FILE *fileptr1, *fileptr2;
    char filename[40];
    char ch;
    int delete_line, temp = 1;
 
    printf("Enter file name: ");
    scanf("%s", filename);
    //open file in read mode
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    //rewind
    rewind(fileptr1);
    printf(" \n Enter line number of the line to be deleted:");
    scanf("%d", &delete_line);
    //open new file in write mode
    fileptr2 = fopen("replica.c", "w");

    while (1) 
    {
        ch = getc(fileptr1);
        if (ch == EOF)
            break;

        if (temp != delete_line)
            putc(ch, fileptr2);

        if (ch == '\n')
            temp++;
    }

    fclose(fileptr1);
    fclose(fileptr2);
    remove(filename);
    //rename the file replica.c to original name
    rename("replica.c", filename);
    printf("\n The contents of file after being modified are as follows:\n");
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    fclose(fileptr1);
    return 0;
}
