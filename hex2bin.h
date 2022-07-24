#include <stdint.h>
#include <stdio.h>

#ifndef HEX2BIN_H_INCLUDED
#define HEX2BIN_H_INCLUDED
#define HEX2BIN(X) printf("Orig number:  0x%x or %d \n",X);printf("0b");hex2bin(X);printf("\n")
//how to write C macros with parameters: https://www.youtube.com/watch?v=JqN4uVgCTWE

void hex2bin(int16_t h); // create text before conv


#endif // HEX2BIN_H_INCLUDED
