/********************************************************************/
/* DEVELOPER:      Gali Aviyam                                      */
/* DATE MODIFIED:  4.12.2022                                        */
/* WORKSHEET NAME: ATOI ITOA                                        */
/* Reviewer:       Karin                                            */
/********************************************************************/
#ifndef ATIT_H
#define ATIT_H

#include <stddef.h>
/******************Macros*******************/
#define IS_LITTLE_ENDIAN (*(unsigned short int *)"\0\xff" > 0x0100)

enum Bool
{	
	FALSE = -1,
	TRUE = 0
};
/****************Functions*****************/
char *ItoaBase10(int num, char *str);
char *ItoaAnyBase(int num, char *str, int base);
int Atoi(const char *str, int base);
void PrintLetters(char *arr1, char *arr2, char *arr3, size_t size1, size_t size2, size_t size3);
int IsLittleEndian(void);

#endif
