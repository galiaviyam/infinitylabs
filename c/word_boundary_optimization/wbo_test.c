/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 25.11.2022                                        */
/* WORKSHEET NAME: word boundary optimization                       */
/* GDB + Valgrind tested                                            */
/* Reviewer: Karin                                                  */
/*------------------------------------------------------------------*/

#include "wbo.h"
#include <stdio.h> /*printf*/

void Test(void);
void TestMemset(char *str, char c, int n);
void TestMemcpy(char *str1, char *str2, int n);
void TestMemmove(char *str1, char *str2, int n);

int main(void)
{
	Test();
	return 0;
}

void Test(void)
{
	char str1[] = {'1', '2', '3', '4', '5', '6', '7', '8', '\0'};
	char str2[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', '\0'};
	char str3[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', '\0'};
	char str4[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', '\0'};
	char str5[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', '\0'};
		
	TestMemset(str1, '$', 4);
	
	TestMemcpy(str2, str3, 4);
	
	TestMemmove(str4, str5, 4);
}

void TestMemset(char *str, char c, int n)
{
	printf("***********Memset**********\n");
	printf("before: %s\n", str);
	Memset((void *)str, c, n);
	printf("after: %s\n", str);
}

void TestMemcpy(char *str1, char *str2, int n)
{
	printf("\n***********Memcpy**********\n");
	printf("before:\nstr1: %s\nstr2: %s\n", str1, str2);
	Memcpy(str1, str2, n);
	printf("\nafter: %s\n", str1);
}

void TestMemmove(char *str1, char *str2, int n)
{
	printf("\n***********Memmove*********\n");
	printf("before:\nstr1: %s\nstr2: %s\n", str1, str2);
	Memmove(str1, str2, n);
	printf("\nafter: %s\n", str1);
}
