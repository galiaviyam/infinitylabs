/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	Hash Table         		*/
/*   Date:		03/02/23				*/
/*	 Reviewer:	Matan					*/
/*										*/
/****************************************/

#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h>		/* size_t */

/*------------------------------- Hash Table ----------------------------------
General Description:
	A hash table is a data structure that uses a hash function to map keys to 
	indexes in an array, allowing for efficient search and insertion operations. 
	Hash tables are commonly used for implementing dictionaries, caches, and 
	other data structures where fast lookups are required.
	
Main Functionality:
	Search
	Insert
	Remove
	
Attributes:
	random access
	fixed size
	ordered value structure
	unique items
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Description:
	A prototype of the callback function to be executed in HashForeach. 
	
Return Value:
	The function should return an int - 0 for success and any non-zero int for 
	failure.
------------------------------------------------------------------------------*/
typedef int (*hash_callback_t)(void *item, void *param);

/*------------------------------------------------------------------------------
Description:
	A prototype of the Hash function. it receives an item and generate an index 
	according to the given key. 
	This API does not handle collisions - If the same index is generated all 
	the values will be chained in the same index.
Return Value:
	The function returns the index generated from the key of the received
	item.
------------------------------------------------------------------------------*/
typedef size_t (*hash_func_t)(const void *key);

/*------------------------------------------------------------------------------
Description:
	A prototype of a function that determines whether two keys match.
Return Value:
	if the keys are a match the function will return 1, otherwise it will
	return 0.
------------------------------------------------------------------------------*/
typedef int (*hash_is_match_t)(const void *key1, const void *key2);

/*------------------------------------------------------------------------------
Description:
	A prototype of the GetKey function - this function gets the item's key.
Return Value:
	The function should return a void pointer to the key.
------------------------------------------------------------------------------*/
typedef void *(*hash_get_key_t)(const void *item);

/*------------------------------------------------------------------------------
Description:
	A data type of the hash table handle.
------------------------------------------------------------------------------*/
typedef struct hash hash_t; 

/*------------------------------------------------------------------------------
Description:
	The HashCreate function allocates the required resources to create a hash 
	table with the size received in table_size.
	
Parameters:
	GetKey - a user function to extract the key from the item.
	IsMatch - a user function to compare keys.
	hash_func - a user function to generate index from the item's key.
	table_size - the number of buckets to be created in the hash table.
	
Return Value:
	The function returns a handle to the hash table.
	
Complexity: 
	time:  O(n) / space: O(n) 
------------------------------------------------------------------------------*/
hash_t *HashCreate(hash_get_key_t GetKey, hash_is_match_t IsMatch, 
								      hash_func_t hash_func, size_t table_size);
								      
/*------------------------------------------------------------------------------
Description:
	The HashDestroy function destroyed all resources created for the hash table.
	
Parameters:
	hash - a handle to the hash table to be destroyed.
	
Complexity: 
	time:  O(n) / space: O(1) 
------------------------------------------------------------------------------*/
void HashDestroy(hash_t *hash);

/*------------------------------------------------------------------------------
Description:
	The HashInsert function inserts an item to the hash table by using the 
	GetKey function to generate the index.
	
Parameters:
	hash - the hash table to store the new item.
	item - a void pointer to the new item.
	
Return Value:
	The function returns 0 for success and 1 for failure.
	
Complexity: 
	time:  O(1) / space: O(1) 
------------------------------------------------------------------------------*/
int HashInsert(hash_t *hash, void *item); 

/*------------------------------------------------------------------------------
Description:
	The HashRemove function removes an item from the hash table.
	
Parameters:
	hash - the hash table from which the item should be removed.
	key - the key of the item to be removed.

Complexity: 
	time: Avg - O(1) , Worst - O(n) / space: O(1) 
------------------------------------------------------------------------------*/
void HashRemove(hash_t *hash, const void *key);

/*------------------------------------------------------------------------------
Description:
	The HashFind function searches for an item according to the key argument, 
	and returns the item if found.
	
Parameters:
	hash - the hash table to search the item in.
	key - the key to be searched in the hash table.
	
Return Value:
	If the item is found, the function returns a void pointer to the item.
	Otherwise it returns NULL.
	
Complexity: 
	time: Avg - O(1) , Worst - O(n) / space: O(1) 
------------------------------------------------------------------------------*/
void *HashFind(const hash_t *hash, const void *key);

/*------------------------------------------------------------------------------
Description:
	The HashForeach function traverses the items in the hash table, and operates
	the callback function on each item.
	Note: if the callback function fails on any item, the function will stop the 
	traverse and return.
Parameters:
	hash - a pointer to the hash table.
	callback - a user function to execute on each item.
	param - a void pointer to the params of callback function.
	
Return Value:
	The function returns 0 for success and 1 for failure.

Complexity: 
	time: O(n)/ space: O(1) 
------------------------------------------------------------------------------*/
int HashForeach(hash_t *hash, hash_callback_t callback, void *param);

/*------------------------------------------------------------------------------
Description:
	The HashSize function counts the number of items stored in the hash table.
	In case of collision, the number of items can be larger than the original
	table_size.
	Note: a callback function that changes the key can cause an undefined
	behavior.
Parameters:
	hash - a pointer to the hash table.
	
Return Value:
	The function returns the number of items stored in the hash table.
	
Complexity: 
	time: O(n) / space: O(1) 
------------------------------------------------------------------------------*/
size_t HashSize(const hash_t *hash);

/*------------------------------------------------------------------------------
Description:
	The HashIsEmpty function checks whether the hash table is empty.
	
Parameters:
	hash - a pointer to the hash table.
	
Return Value:
	The function returns 1 if the hash table is empty. Otherwise it returns 0.
	
Complexity: 
	time: O(table_size) / space: O(1) 
------------------------------------------------------------------------------*/
int HashIsEmpty(const hash_t *hash);

#endif /* __HASH_H__ */

