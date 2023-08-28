/*****************************************/
/*										 */   
/*	 Developer: Gali Aviyam				 */
/*   Project: sorted list		  	 	 */
/*   Last Modified:	20/12/22			 */
/*	 Reviewer: Sveta					 */
/*					 					 */
/*****************************************/
#include <assert.h>			/* assert */
#include <stdlib.h>			/* malloc */

#include "sort_list.h"      /*sorted linked list*/
#include "dlist.h"      	/*doubly linked list*/

struct sort_list
{
	dlist_t *dlist;
	sort_list_cmp_t cmp;
};

static sort_list_iter_t DIterToSortIter(dlist_iter_t d_iter, sort_list_t *list);
static dlist_iter_t SortListToDlistIter(sort_list_iter_t iter);
static dlist_t *SortListToDlist(const sort_list_t *list);

/*------------------------------SortlistCreate-------------------------------*/
sort_list_t *SortListCreate(sort_list_cmp_t cmp)
{
	sort_list_t *list = NULL;
	
	assert(NULL != cmp);
	
	list = (sort_list_t *)malloc(sizeof(sort_list_t));
	if (NULL == list)
	{
		return NULL;
	}
	
	list->dlist = DlistCreate();
	if (NULL == list->dlist)
	{
		free(list);
		list = NULL;
		return NULL;
	}
	
	list->cmp = cmp;
	
	return list;
}

/*------------------------------SortlistDestroy-------------------------------*/
void SortListDestroy(sort_list_t *list)
{
	assert(NULL != list);
	
	DlistDestroy(list->dlist);
	
	free(list);
	list = NULL;
}

/*------------------------------SortListInsert--------------------------------*/
sort_list_iter_t SortListInsert(sort_list_t *list, void *data)
{
	sort_list_iter_t s_iter = {0};
	sort_list_iter_t end = {0};
	
	assert(NULL != list);
	assert(NULL != data);
	
	s_iter = SortListBegin(list);
	end = SortListEnd(list);
	
	while (!SortListIterIsEqual(s_iter, end) && 
			list->cmp(SortlistGetVal(s_iter), data) < 0)
	{
		s_iter = SortListNext(s_iter);
	}
	
	s_iter.iter = DlistInsertBefore(s_iter.iter, data);
	
	return s_iter;
}

/*------------------------------SortListRemove--------------------------------*/
sort_list_iter_t SortListRemove(sort_list_iter_t iter)
{
	assert(NULL != SortListToDlistIter(iter));
	
	iter.iter = DlistRemove(SortListToDlistIter(iter));
	
	return iter;
}

/*-------------------------------SortListFind---------------------------------*/
sort_list_iter_t SortListFind(const sort_list_t *list ,const sort_list_iter_t from,
							 const sort_list_iter_t to, const void *param)
{
	sort_list_iter_t iter_found = {0};
	
	assert(NULL != list);
	assert(from.list == to.list);

	iter_found = from;
	
	while (!SortListIterIsEqual(iter_found, to) && 
			0 != list->cmp(SortlistGetVal(iter_found), param))
	{
		iter_found = SortListNext(iter_found);
	}
	
	return iter_found;
}

/*------------------------------SortListFindIf--------------------------------*/				 
sort_list_iter_t SortListFindIf(const sort_list_iter_t from, 
							   const sort_list_iter_t to, 
							   sort_list_is_match_t is_match, void *param)
{
	sort_list_iter_t iter_found = {0};
	
	assert(from.list == to.list);

	iter_found.iter = DlistFind(SortListToDlistIter(from), 
					SortListToDlistIter(to), is_match, param);
	#ifndef NDEBUG
		iter_found.list = from.list;
	#endif
	
	return iter_found;
} 

/*-----------------------------SortListForEach--------------------------------*/
int SortListForEach(sort_list_iter_t from, sort_list_iter_t to, 
			        sort_list_do_action_t do_action, void *param)
{
	assert(from.list == to.list);

	return (DlistForEach(SortListToDlistIter(from), SortListToDlistIter(to),
						 do_action, param));
}

/*------------------------------SortListBegin---------------------------------*/
sort_list_iter_t SortListBegin(const sort_list_t *list)
{
	assert(NULL != list);
	
	return (DIterToSortIter(DlistBegin(SortListToDlist(list)), 
							(sort_list_t *)list));
}

/*------------------------------SortListEnd---------------------------------*/
sort_list_iter_t SortListEnd(const sort_list_t *list)
{
	assert(NULL != list);
	
	return (DIterToSortIter(DlistEnd(SortListToDlist(list)), 
							(sort_list_t *)list));
}

/*------------------------------SortListNext---------------------------------*/
sort_list_iter_t SortListNext(sort_list_iter_t current)
{
	assert(NULL != SortListToDlistIter(current));
	
	current.iter = DlistNext(SortListToDlistIter(current));
	
	return current;
}

/*------------------------------SortListPrev---------------------------------*/
sort_list_iter_t SortListPrev(sort_list_iter_t current)
{
	assert(NULL != SortListToDlistIter(current));
	
	current.iter = DlistPrev(SortListToDlistIter(current));
	
	return current;
}

/*------------------------------SortlistGetVal--------------------------------*/
void *SortlistGetVal(const sort_list_iter_t iter)
{
	assert(NULL != SortListToDlistIter(iter));
	
	return (DlistGetVal(SortListToDlistIter(iter)));
}

/*----------------------------SortListIterIsEqual-----------------------------*/
int SortListIterIsEqual(const sort_list_iter_t one, const sort_list_iter_t other)
{
	assert(NULL != SortListToDlistIter(one));
	assert(NULL != SortListToDlistIter(other));
	
	return(DlistIterIsEqual(SortListToDlistIter(one), 
							SortListToDlistIter(other)));
}

/*-------------------------------SortListCount--------------------------------*/
size_t SortListCount(const sort_list_t *list)
{
	assert(NULL != list);
	
	return (DlistCount(SortListToDlist(list)));
}

/*------------------------------SortListIsEmpty-------------------------------*/
int SortListIsEmpty(const sort_list_t *list)
{
	assert(NULL != list);
	
	return (DlistIsEmpty(SortListToDlist(list)));
}

/*------------------------------SortListPopFront------------------------------*/
void *SortListPopFront(sort_list_t *list)
{
	assert(NULL != list);
	
	return (DlistPopFront(SortListToDlist(list)));
}

/*------------------------------SortListPopBack-------------------------------*/
void *SortListPopBack(sort_list_t *list)
{
	assert(NULL != list);
	
	return (DlistPopBack(SortListToDlist(list)));
}

/*-------------------------------SortListMerge--------------------------------*/
void SortListMerge(sort_list_t *dest, sort_list_t *src)
{
	sort_list_iter_t dest_iter = {0};
	sort_list_iter_t dest_end = {0};
	sort_list_iter_t src_iter = {0};
	sort_list_iter_t src_end = {0};
	int cmp_res = 0;
	
	assert(NULL != dest);
	assert(NULL != dest->dlist);
	assert(NULL != src);
	assert(NULL != src->dlist);
	assert(dest->cmp == src->cmp);

	dest_iter = SortListBegin(dest);
	dest_end = SortListEnd(dest);
	src_iter = SortListBegin(src);
	src_end = SortListEnd(src);
	
	while ((!SortListIterIsEqual(dest_iter, dest_end)) && 
			(!SortListIterIsEqual(src_iter, src_end)))
	{
		cmp_res = dest->cmp(SortlistGetVal(dest_iter), SortlistGetVal(src_iter));
		if (cmp_res >= 0)
		{
			DlistSplice(SortListToDlistIter(src_iter), 
						SortListToDlistIter(SortListNext(src_iter)), 
						SortListToDlistIter(dest_iter));
			src_iter = SortListBegin(src);
		}
		else
		{
			dest_iter = SortListNext(dest_iter);
		}
	}
	if (!SortListIterIsEqual(src_iter, src_end))
	{
		DlistSplice(SortListToDlistIter(src_iter), SortListToDlistIter(src_end),
					 SortListToDlistIter(dest_iter));
	}
}

/*----------------------------Helper functions--------------------------------*/
static sort_list_iter_t DIterToSortIter(dlist_iter_t d_iter, sort_list_t *list)
{
	sort_list_iter_t sort_iter = {0};
	
	assert(NULL != list);
	
	sort_iter.iter = d_iter;
	
	#ifndef NDEBUG
		sort_iter.list = list;
	#endif

	return sort_iter;
}

static dlist_iter_t SortListToDlistIter(sort_list_iter_t iter)
{	
	return iter.iter;	
}

static dlist_t *SortListToDlist(const sort_list_t *list)
{
	assert(list);
	
	return list->dlist;
}
