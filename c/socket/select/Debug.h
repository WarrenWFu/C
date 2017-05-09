
#ifndef DEBUG_H
#define DEBUG_H

//#define NDEBUG
#include <assert.h>


void printData(uint8_t *data, uint32_t size);


#ifndef NDEBUG

#define DEBUG_PRINT_DATA(data, size)  printData(data, size)
#define DEBUG_PRINTF(...)  fprintf(stderr, ...)   

#else

#define DEBUG_PRINT_DATA(data, size) 
#define DEBUG_PRINTF(...)  


#endif

#endif

