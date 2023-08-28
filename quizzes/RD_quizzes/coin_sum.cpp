#include <iostream>     // cout
#include <sys/types.h>	// ssize_t
#include <cstdint>		// SIZE_MAX

using std::cout;
using std::endl;

ssize_t CoinChange(size_t *coins, size_t size, size_t sum);
static void TestResEqual(int result, int expected);

int main(void)
{
	size_t coins[4][3] = {{1, 2, 5}, {1, 5, 10}, {1, 10, 20}, {5, 20, 30}};
	size_t sum[4] = {13, 37, 39, 29};
	ssize_t results[4] = {4, 6, 11, -1};

	for (int i = 0; 4 > i; ++i)
	{
		TestResEqual(CoinChange(coins[i], 3, sum[i]), results[i]);
	}

	return 0;
}

ssize_t CoinChange(size_t *coins, size_t size, size_t sum)
{
	if (0 == sum)
	{
		return 0;
	}

	size_t res = SIZE_MAX;

	for (size_t i = 0; i < size; ++i)
	{
		if (sum >= coins[i])
		{
			size_t sub_res = CoinChange(coins, size, sum - coins[i]);

			if ((SIZE_MAX != sub_res) && (sub_res + 1 < res))
			{
				res = sub_res + 1;
			}
		}
	}

	return res;
}

static void TestResEqual(int result, int expected)
{
	if (expected == result)
	{
		cout << "\033[32mPass\033[0m" << endl;
	}
	else
	{
		cout << "\033[31mFAILURE\033[0m" << endl;
	}
}