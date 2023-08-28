#include <iostream>	// cout
#include <cassert>	//assert

using std::cout;
using std::endl;

void TestMemcpy(char *str1, char *str2, int n);

int main(void)
{
	// -------- 1 --------
	cout << "***********Memcpy**********" << endl;
	char str1[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', '\0'};
	char str2[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', '\0'};
	
	TestMemcpy(str1, str2, 4);
	
	// -------- 2 --------
	cout << "\n***********pointers**********" << endl;
	int a = 7;
	int *ptr = &a;
	
	cout << ptr << endl;
	cout << *ptr << endl;
	
	*(char *)&ptr = 1;
	
	cout << ptr << endl;
	cout << *ptr << endl;
	
	return 0;
}

void *Memcpy(void *dest, const void *src, size_t num_of_bytes)
{
	void *dest_runner = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	dest_runner = dest;
	
	while (num_of_bytes--)
	{
		*(char *)dest_runner = *(char *)src;
		src = (char *)src + 1;
		dest_runner = (char *)dest_runner + 1;
	}
	
	return dest;
}

void TestMemcpy(char *str1, char *str2, int n)
{
	cout << "before:\nstr1: " << str1 << "\nstr2: " << str2 << endl;
	Memcpy(str1, str2, n);
	cout << "\nafter: " << str1 << endl;
}
