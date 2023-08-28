#include <string.h>	/* strlen */
#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */

#define ASCII (256)

static char *MinWindowSubstring(const char *big, const char *small, char *res);
static void InitLut(int *dst, const char *src, size_t len);
static int IsInWindow(const int *small, const int *big);

int main()
{
	char res[256] = {0};
	
	MinWindowSubstring("ombabadugunda", "nau", res);
	printf("%s\n", res);

	return 0;
}

static char *MinWindowSubstring(const char *big, const char *small, char *res)
{	
	int small_lut[ASCII] = {0};
	int tmp_lut[ASCII] = {0};
	size_t big_len = 0;
	size_t small_len = 0;
	size_t min_size = 0;
	const char *min_ptr = NULL;
	size_t begin = 0;
	size_t end = 0;

	assert(big);
	assert(small);
	
	big_len = strlen(big);
	small_len = strlen(small);
	min_size = big_len + 1;
	
	InitLut(small_lut, small, small_len);
	
	while (begin <= (big_len - small_len) && (end <= big_len))
	{
		while ((0 == small_lut[(int)big[begin]]) && begin < (big_len - small_len))
		{
			++begin;
		}
		
		end = end > begin ? end : begin;
		
		while ((!IsInWindow(small_lut, tmp_lut) && (end <= big_len)))
		{
			++tmp_lut[(int)big[end]];
			++end;
		}
		
		if ((end - begin) <= min_size && IsInWindow(small_lut, tmp_lut))
		{
			min_size = end - begin;
			min_ptr = big + begin;
		}
		
		--tmp_lut[(int)big[begin]];
		++begin;
	}
	
	strncpy(res, min_ptr, min_size);
	res[min_size] = '\0';
	
	return res;
}

static int IsInWindow(const int *small, const int *big)
{
	size_t i = 0;
	int is_in = 1;
	
	for (i = 0; i < ASCII && is_in; ++i)
	{
		is_in = small[i] <= big[i];
	}
	
	return is_in;
}

static void InitLut(int *lut, const char *src, size_t size)
{
	size_t i = 0;
	
	assert(lut);
	assert(src);
	
	for (i = 0; i < size; ++i)
	{
		++lut[(int)src[i]];
	}
}
