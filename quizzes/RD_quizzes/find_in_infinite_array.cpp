#include <iostream>
#include <climits>
using namespace std;

long long findInfiniteArray(const long long arr[], long long num)
{
    long long jump = num;
    long long i = 0;

    while (arr[jump] < num)
    {
        i = jump;
        jump *= 2;
    }

    while (arr[i] < num)
    {
        ++i;
    }

    if (num != arr[i])
    {
        return -1;
    }

    return i;
}

int main()
{
    long long arr[5000] = {0};
    long long target = 666;

    for (int i = 0; i < 5000; ++i)
    {
        arr[i] = i * 2;
    }

    long long index = findInfiniteArray(arr, target);

    if (index != -1)
    {
        cout << "Element found at index " << index << endl;
    }
    else
    {
        cout << "Element not found" << endl;
    }

    return 0;
}