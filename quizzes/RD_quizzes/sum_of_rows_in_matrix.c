#include <stdio.h>

void GetRowsSum(int **matrix, size_t rows, size_t cols, int *res)
{
	size_t i = 0;
	size_t j = 0;
	int row_sum = 0;
	
	for (i = 0; i < rows; ++i)
	{
		row_sum = 0;
		for (j = 0; j < cols; ++j)
		{
			row_sum += ((int *)matrix)[i * cols + j];
		}
		
		res[i] = row_sum;
	}
}

int main(void)
{
	int matrix[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
	int res[3] = {0};
	size_t i = 0;
	
	GetRowsSum((int **)matrix, 3, 4, res);
	
	for (i = 0; i < 3; ++i)
	{
		printf("%d\n", res[i]);
	}
	return 0;
}
