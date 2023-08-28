/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Hash Table         		*/
/*   Date:		03/02/23				*/
/*	 Reviewer:	Matan					*/
/*										*/
/****************************************/

#include <stdlib.h>		/* malloc */
#include <assert.h>		/* assert */	

#include "hash_table.h"	/* hash table header file */
#include "dlist.h"		/* doubly linked list header file */

enum status
{
	SUCCESS = 0,
	FAIL = -1
} status_t;

enum bool
{
	FALSE = 0,
	TRUE
} bool_t;

struct hash
{
	size_t table_size; 
	hash_get_key_t get_key;
	hash_is_match_t is_match;
	hash_func_t hash_func;
	dlist_t *table[1];
}; 

static void InitTable(hash_t *hash, hash_get_key_t GetKey, 
			hash_is_match_t IsMatch, hash_func_t hash_func, size_t table_size);

/*------------------------------HashCreate-----------------------------------*/
hash_t *HashCreate(hash_get_key_t GetKey, hash_is_match_t IsMatch, 
								      hash_func_t hash_func, size_t table_size)
{
	hash_t *hash = NULL;
	
	assert(NULL != GetKey);
	assert(NULL != IsMatch);
	assert(NULL != hash_func);
	assert(0 < table_size);
	
	hash = (hash_t *)calloc(1, sizeof(hash_t) + 
						((table_size) * sizeof(dlist_t *)));
	if (NULL == hash)
	{
		return NULL;
	}
	
	
	InitTable(hash, GetKey, IsMatch, hash_func, table_size);
	
	return hash;
}

/*------------------------------HashDestroy---------------------------------*/
void HashDestroy(hash_t *hash)
{
	size_t i = 0;

	assert(NULL != hash);

	for (i = 0; i < hash->table_size; ++i)
	{
		if (NULL != hash->table[i])
		{
			DlistDestroy(hash->table[i]);
			hash->table[i] = NULL;
		}
	}

	free(hash);
	hash = NULL;
}

/*------------------------------HashInsert---------------------------------*/
int HashInsert(hash_t *hash, void *item)
{
	size_t index = 0;
	int status = SUCCESS;
	dlist_iter_t new_entry = NULL;
	
	assert(NULL != hash);
	assert(NULL != item);
		
	index = hash->hash_func(hash->get_key(item));
	
	if (NULL == hash->table[index])
	{
		hash->table[index] = DlistCreate();
		if (NULL == hash->table[index])
		{
			return FAIL;
		}
	}
	
	new_entry = DlistPushBack(hash->table[index], item);
	if (DlistIterIsEqual(DlistEnd(hash->table[index]), new_entry))
	{
		status = FAIL;
	}

	return status;
}

/*------------------------------HashRemove---------------------------------*/
void HashRemove(hash_t *hash, const void *key)
{
	size_t index = 0;
	dlist_iter_t item = 0;
	dlist_t *list = NULL;

	assert(NULL != hash);
	assert(NULL != key);
	
	index = hash->hash_func(key);
	list = hash->table[index];
	
	if (NULL != list)
	{
		item = DlistFind(DlistBegin(list), DlistEnd(list), 
				(dlist_is_match_t)hash->is_match, (void *)key);
		if (!DlistIterIsEqual(DlistEnd(list), item))
		{
			DlistRemove(item);
		}
	}
}

/*------------------------------HashFind---------------------------------*/
void *HashFind(const hash_t *hash, const void *key)
{
	size_t index = 0;
	dlist_iter_t iter = NULL;
	dlist_t *list = NULL;
	void *ret_val = NULL;
	
	assert(NULL != hash);
	assert(NULL != key);
	
	index = hash->hash_func(key);
	list = hash->table[index];
	
	if (NULL != list)
	{
		iter = DlistFind(DlistBegin(list), DlistEnd(list), 
					(dlist_is_match_t)hash->is_match, (void *)key);
				
		if (!DlistIterIsEqual(DlistEnd(list), iter))
		{
			ret_val = DlistGetVal(iter);
		}
	}
	
	return ret_val;
}

/*------------------------------HashForeach---------------------------------*/
int HashForeach(hash_t *hash, hash_callback_t callback, void *param)
{
	int status = SUCCESS;
	size_t i = 0;
	
	assert(NULL != hash);
	assert(NULL != callback);
	
	for (i = 0; i < hash->table_size && !status; ++i)
	{
		if (NULL != hash->table[i])
		{
			status = DlistForEach(DlistBegin(hash->table[i]), 
					DlistEnd(hash->table[i]), callback, param);
		}
	}

	return status;
}

/*------------------------------HashSize---------------------------------*/
size_t HashSize(const hash_t *hash)
{
	size_t i = 0;
	size_t count = 0;

	assert(NULL != hash);
		
	for (i = 0; i < hash->table_size; ++i)
	{
		if (NULL != hash->table[i])
		{
			count += DlistCount(hash->table[i]);
		} 
	}
	
	return count;
}

/*------------------------------HashIsEmpty---------------------------------*/
int HashIsEmpty(const hash_t *hash)
{
	assert(NULL != hash);
	
	return (0 == HashSize(hash));
}

/*--------------------------------------------------------------------------*/
/*----------------------------Static functions------------------------------*/
/*--------------------------------------------------------------------------*/

static void InitTable(hash_t *hash, hash_get_key_t GetKey, 
			hash_is_match_t IsMatch, hash_func_t hash_func, size_t table_size)
{
	assert(NULL != GetKey);
	assert(NULL != IsMatch);
	assert(NULL != hash_func);
	assert(0 < table_size);
	
	hash->get_key = GetKey;
	hash->is_match = IsMatch;
	hash->hash_func = hash_func;
	hash->table_size = table_size;
}
