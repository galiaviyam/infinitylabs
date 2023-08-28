/********************************************************************/
/* DEVELOPER:      Gali Aviyam                                      */
/* DATE MODIFIED:  4.12.2022                                        */
/* WORKSHEET NAME: ATOI ITOA                                        */
/* Reviewer:       Karin                                            */
/********************************************************************/
#include "atit.h"
#include <stdio.h>/*printf*/
void Tests(void);
void TestItoaBase10(void);
void TestItoaAnyBase(void);
void TestAtoi(void);
void TestPrintLetters(void);
void TestIsLittleEndian(void);
void TestIsLittleEndianMacro(void);

int main(void)
{
	Tests();
	return 0;
}

void Tests(void)
{
	printf("************TestItoaBase10************\n");
	TestItoaBase10();
	
	printf("\n**********TestItoaAnyBase***********\n");
	TestItoaAnyBase();
	
	printf("\n**************TestAtoi**************\n");
	TestAtoi();
	
	printf("\n**********TestPrintLetters**********\n");
	TestPrintLetters();

	printf("\n*********TestIsLittleEndian*********\n");
	TestIsLittleEndian();	

	printf("\n******TestIsLittleEndianMacro*******\n");
	TestIsLittleEndianMacro();
}

void TestItoaBase10(void)
{
	char str1[10] = {'\0'};
	char str2[10] = {'\0'};
	char str3[10] = {'\0'};
	
	printf("64 base 10: %s\n-127 base 10: %s\n 0 base 10: %s\n",
			ItoaBase10(64, str1),
			ItoaBase10(-127, str2),
			ItoaBase10(0, str3));
}

void TestItoaAnyBase(void)
{
	char str1[10] = {'\0'};
	char str2[10] = {'\0'};
	char str3[10] = {'\0'};
	char str4[10] = {'\0'};
	char str5[10] = {'\0'};
	char str6[10] = {'\0'};
	char str7[10] = {'\0'};

	printf("127 base 2: %s\n", ItoaAnyBase(127, str1, 2));
	printf("64 base 8: %s\n", ItoaAnyBase(64, str2, 8));
	printf("12345 base 10: %s\n", ItoaAnyBase(12345, str3, 10));
	printf("-4 base 10: %s\n", ItoaAnyBase(-4, str4, 10));
	printf("64 base 16: %s\n", ItoaAnyBase(64, str5, 16));
	printf("100 base 32: %s\n", ItoaAnyBase(100, str6, 32));
	printf("9876 base 36: %s\n", ItoaAnyBase(9876, str7, 36));
}

void TestAtoi(void)
{
	char str2[] = "654";
	char str8[] = "80";
	char str10[] = "12345";
	char str16[] = "64";
	char str32[] = "900";
	
	printf("654 Base 2: %d\n",Atoi(str2, 2));
	printf("80 Base 8: %d\n",Atoi(str8, 8));
	printf("12345 Base 10: %d\n",Atoi(str10, 10));
	printf("64 Base 16: %d\n",Atoi(str16, 16));
	printf("900 Base 32: %d\n",Atoi(str32, 32));
}

void TestPrintLetters(void)
{
	char arr5[] = {'b', 'a', 'd', 'c', 'f', 'e','z'};
	char arr6[] = {'a', 'b', 'c', 'a', 'e', 'z', 'd'};
	char arr7[] = {'b', 'c'};
	
	PrintLetters(arr5, arr6, arr7, 7, 7, 2);
}

void TestIsLittleEndian(void)
{
	if (0 == IsLittleEndian())
	{
		printf("This computer is Little-Endian\n");
	}
	else
	{
		printf("This computer is Big-Endian\n");
	}
}

void TestIsLittleEndianMacro(void)
{
	if (IS_LITTLE_ENDIAN)
	{
		printf("This computer is Little-Endian\n");
	}
	else
	{
		printf("This computer is Big-Endian\n");
	}
}
