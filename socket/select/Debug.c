
#include <stdio.h>
#include <stdint.h>

void printData(uint8_t *data, uint32_t size)
{
	int    i = 0;

	for (i=0; i<size; i++)
	{
		printf("data[%d] = %02X\n", 
			i, data[i]);
	}
}















