#include <cstdio>
#include <iostream> //cout


inline void foo()
{
    std::cout << "Hello-World";
}
int main()
{
	const int i = 3;
    int *ip = (int*)&i;
    
    *ip = 5;
    int arr[i];

    printf("%d %d\n", i, *ip);

	foo();
    return 0;
}


