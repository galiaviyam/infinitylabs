/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Hash Table         		*/
/*   Date:		03/02/23				*/
/*	 Reviewer:	Matan					*/
/*										*/
/****************************************/

#include <stdio.h>		/* printf */
#include <assert.h>		/* assert */	
#include <string.h>		/* strcmp, strchr */
#include <stdlib.h>		/* malloc */

#include "hash_table.h"	/* hash table header file */

#define TABLE_SIZE (10)
#define DICT_SIZE (26)
#define MAX_STRLEN (256)
#define BYTES_IN_DICT (985084)

enum status
{
	SUCCESS = 0,
	FAIL = 1
};

typedef struct item
{
	int key;
	int value;
	
}item_t;

static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestResultNotNull(void *result);
static void TestBoolResult(int result);
static void TestStatusResult(int result);

static size_t HashFunc(const void *item);
static void *GetKey(const void *item);
static int IsMatch(const void *item1, const void *item2);
static int PrintVal(void *item, void *param);

static void TestCreateDestroy(void);
static void HashInsertTest(void);
static void SizeTest(hash_t *hash_table, size_t expected);
static void HashRemoveTest(void);
static void HashFindTest(void);
static void HashForeachTest(void);

static void LoadDictionaryTest(void);
static size_t HashString(const void *buffer);
static void *GetWord(const void *word);
static int StringIsMatch(const void *word1, const void *word2);

int main(void)
{
	TestCreateDestroy();
	HashInsertTest();
	HashRemoveTest();
	HashFindTest();
	HashForeachTest();
	LoadDictionaryTest();
	
	return 0;
}

static void TestCreateDestroy(void)
{
	hash_t *hash_table = NULL;
		
	hash_table = HashCreate(&GetKey, &IsMatch, &HashFunc, TABLE_SIZE);
	
	printf("create: ");
	TestResultNotNull(hash_table);
	
	printf("is empty: ");
	TestBoolResult(HashIsEmpty(hash_table));
	printf("\n");

	HashDestroy(hash_table);
}

static void HashInsertTest(void)
{
	hash_t *hash_table = NULL;
	item_t items[] = {{14, 1400}, {15, 6000}, {6, 23}};
	size_t i = 0;
	
	printf("----------insert----------\n");
	
	hash_table = HashCreate(&GetKey, &IsMatch, &HashFunc, TABLE_SIZE);
	if (NULL == hash_table)
	{
		printf("\033[0;31mCREATE FAILED\033[0m\n");
		return;
	}
	
	for (i = 0; i < 3; ++i)
	{
		printf("Insert test %lu:	", i+1);
		TestStatusResult(HashInsert(hash_table, (items + i)));
	}
	SizeTest(hash_table, 3);
	
	HashDestroy(hash_table);
}

static void SizeTest(hash_t *hash_table, size_t expected)
{
	printf("\nsize: ");
	TestNumResultEqual(HashSize(hash_table), expected);
}

static void HashRemoveTest(void)
{
	hash_t *hash_table = NULL;
	item_t items[] = {{14, 1400}, {15, 1500}, {6, 600}, {9, 900}};
	size_t i = 0;
	const void *key = NULL;

	printf("----------remove----------\n");
	
	hash_table = HashCreate(&GetKey, &IsMatch, &HashFunc, TABLE_SIZE);
	if (NULL == hash_table)
	{
		printf("\033[0;31mCREATE FAILED\033[0m\n");
		return;
	}
	
	for (i = 0; i < 4; ++i)
	{
		HashInsert(hash_table, (items + i));
	}

	key = (GetKey((void *)(items + 1)));
	
	HashRemove(hash_table, key);
	
	TestNumResultEqual(HashSize(hash_table), 3);
	
	HashDestroy(hash_table);
}

static void HashFindTest(void)
{
	hash_t *hash_table = NULL;
	item_t items[] = {{14, 1400}, {15, 1500}, {6, 600}, {9, 900}};
	size_t values[] = {1400, 1500, 600, 900};
	size_t i = 0;
	const void *key = NULL;
	item_t *item = NULL;
	
	printf("----------find----------\n");
	
	hash_table = HashCreate(&GetKey, &IsMatch, &HashFunc, TABLE_SIZE);
	if (NULL == hash_table)
	{
		printf("\033[0;31mCREATE FAILED\033[0m\n");
		return;
	}
	
	for (i = 0; i < 4; ++i)
	{
		HashInsert(hash_table, (items + i));
	}
	
	for (i = 0; i < 4; ++i)
	{
		key = (GetKey((void *)(items + i)));
		item = (item_t *)HashFind(hash_table, key);
		TestNumResultEqual(item->value, values[i]);
	}

	HashDestroy(hash_table);
}

static void HashForeachTest(void)
{
	hash_t *hash_table = NULL;
	item_t items[] = {{14, 1400}, {15, 1500}, {6, 600}, {9, 900}};
	size_t i = 0;
	void *param = NULL;

	printf("----------foreach----------\n");
	
	hash_table = HashCreate(&GetKey, &IsMatch, &HashFunc, TABLE_SIZE);
	if (NULL == hash_table)
	{
		printf("\033[0;31mCREATE FAILED\033[0m\n");
		return;
	}
	
	for (i = 0; i < 4; ++i)
	{
		HashInsert(hash_table, (items + i));
	}
	
	TestStatusResult(HashForeach(hash_table, &PrintVal, param));
	
	HashDestroy(hash_table);
}

static void LoadDictionaryTest(void)
{
	hash_t *dict_hash = NULL;
	char *dict_buff = NULL;
	char *runner = NULL;
	char word[MAX_STRLEN] = {'\0'};
	FILE *dict_ptr = NULL;
	
	dict_ptr = fopen("/usr/share/dict/words", "r");
	if (NULL == dict_ptr)
	{
		printf("\033[0;31mFAIL\033[0m\n");
		return;
	}
	
	dict_buff = (char *)malloc((BYTES_IN_DICT + 1) * sizeof(char));
	if (NULL == dict_buff)
	{
		printf("\033[0;31mFAIL\033[0m\n");
		return;
	}
	
	fread(dict_buff, BYTES_IN_DICT, 1, dict_ptr);
	
	runner = dict_buff;
	*(runner + BYTES_IN_DICT) = '\0';
	
	dict_hash = HashCreate(&GetWord, &StringIsMatch, &HashString, 270);
	
	while ('\0' != *runner)
	{
		if (0 != HashInsert(dict_hash, runner))
		{
			printf("\033[0;31mFAIL\033[0m\n");
		}
		runner = strchr(runner, '\n');
		*runner = '\0';
		++runner;
	}
	
	printf("\nPress 0 to exit-\n");
	do
	{
		printf("\nEnter a word to search in the dictionary:\n");
		if (EOF == scanf("%s", word))
		{
			printf("\033[0;31mFAIL\033[0m\n");
		}
		
		if (NULL != HashFind(dict_hash, word))
		{
			printf("\033[0;32mFound\033[0m\n");
		}
		else
		{
			printf("\033[0;31mNot found\033[0m\n");
		}
	}while (0 != strcmp("0", word));
	
	fclose(dict_ptr);
	dict_ptr = NULL;   	
	
	free(dict_buff);
	dict_buff = NULL;
	
	HashDestroy(dict_hash);
	dict_hash = NULL;
}

/**************************test service functions*************************/

static size_t HashString(const void *key)
{
    unsigned char *word = NULL;
	
	assert(key);
	
	word = (unsigned char *)key;
	
	return ((*word + *(word + 1)) % (DICT_SIZE * 2));

}

static size_t HashFunc(const void *key)
{
	size_t index = 0;
		
	assert(NULL != key);
	
	index = *((size_t *)key) % 10;
	
	return index;
}

static void *GetKey(const void *item)
{
	assert(NULL != item);
	
	return &((item_t *)(item))->key;
}

static int IsMatch(const void *key1, const void *key2)
{
	return (*(int *)key1 == *(int *)key2);
}

static int PrintVal(void *item, void *param)
{	
	assert(NULL != item);
	
	printf("%d\n", *(int *)GetKey(item));
	(void)param;
	
	return 0;
}

static void *GetWord(const void *word)
{
	assert(NULL != word);

	return ((char *)word);	
}

static int StringIsMatch(const void *word1, const void *word2)
{
	assert(NULL != word1);
	assert(NULL != word2);
	
	return (0 == strcmp((char *)word1, (char *)word2));
}
/**************************test utility functions************************/
static void TestStatusResult(int result)
{
	if (result == SUCCESS)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestBoolResult(int result)
{
	if (result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestNumResultEqual(size_t result, size_t expected_result)
{
	if (result == expected_result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestResultNotNull(void *result)
{
	if (NULL != result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}
