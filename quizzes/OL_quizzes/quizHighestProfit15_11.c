#include <stdio.h>

int FindHighestProfit(int *stocks, size_t size, int *buy, int *sell)
{
	int *min = stocks;
	int *max = stocks;
	int *curr_price = stocks;
	int profit = 0;
	
	while (size --)
	{
		if (*curr_price > *max)
		{
			max = curr_price;
		}
		if (*curr_price < *min)
		{
			min = curr_price;
			max = curr_price;
		}
		if (*max - *min > profit)
		{
			profit = *max - *min;
			*buy = min - stocks;
			*sell = max - stocks;
		}
		++curr_price;
	}
	return profit;
}

int main()
{
	int arr[8] = {6, 12, 3, 5, 1, 4, 9, 2};
	int buy = 0;
	int sell = 0;
	int profit = FindHighestProfit(arr, 8, &buy, &sell);
	
	printf("highest profit: %d\nbuy index: %d\nsell index: %d\n", profit, buy, sell);
	
	return 0;
}
