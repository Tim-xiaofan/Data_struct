/** 20210323 22:37, zyj, GuangDong*/
//list.c
#include <stdlib.h>
#include <stdio.h>
#include "sqlist.h"


item * 
item_new(void)
{
	item *e;
	e = (item *) malloc(sizeof(item));
	return e;
}

/** do not attempt to access an item after deleting it.*/
void 
item_delete(item * e)
{
	free(e);
}

void 
item_assign(item *e1, item e2)
{
	*e1 = e2;
}

short 
item_compare(item e1, item e2)
{
	if(e1 > e2) return 1;
	if(e1 == e2) return 0;
	return -1;
}

/** less than or equal*/
bool 
item_le(item e1, item e2)
{
	return (e1 <= e2);
}

bool
item_equal(item e1, item e2)
{
	return (e1 == e2);
}

void
item_show(item e)
{
	printf("%d", e);
}

sqlist* 
sqlist_new(int size)
{
	sqlist *l;

	if(size <= 0)
	{
		fprintf(stderr, "invalid size\n");
		return NULL;
	}

	l = (sqlist *)malloc(sizeof(sqlist));
	if(l == NULL)
	{
		printf("can not alloc buffer for sqlist\n");
		return NULL;
	}

	l->length = 0;
	l->size = size;
	/** alloc memory for items*/
	l->items = (item *)malloc(sizeof(item) * size);
	return l;
}

/** O(1) 
 *	there is no out of bounds check*/
bool
sqlist_get_n(const sqlist *l, int i, item * e)
{
	item_assign(e, l->items[i]);
	return true;
}

/** O(1)*/
bool 
sqlist_append(sqlist *l, item e)
{
	if(l->length == l->size)
	{
		printf("sqlist is full\n");
		return false;
	}

	item_assign(&(l->items[l->length++]), e);
	return true;
}

/**O(n) */
bool 
sqlist_append_bulk(sqlist *l, const item *es, int n)
{
	int i;

	if(n > (l->size - l->length))
	{
		printf("not enough space.\n");
		return false;
	}

	for(i = 0; i < n; i++)
		sqlist_append(l, es[i]);
	return true;
}

int 
sqlist_length(const sqlist *l)
{
	return l->length;
}


/** O(n)*/
void sqlist_show(const sqlist *l, pitem_show pf)
{
	int i;

	if(l->length == 0)
	{
		printf("empty sqlist");
		return;
	}

	for(i = 0; i < l->length; i++)
	{
		(*pf)(l->items[i]);
		printf(" ");
	}
	printf("\n");
}

/** @return -1 indicates e is not in sqlist , or return index
 *	O(n)*/
int 
sqlist_search(const sqlist *l, const item e, pitem_equal pf)
{
	int i;
	bool found;

	found = false;
	for(i = 0; i < l->length; i++)
	{
		if((*pf)(e, l->items[i]))
		{
			found = true;
			break;
		}
	}

	if(found) return i;
	else return -1;
}

/** do not attempt to access a sqlist after deleting it.*/
void sqlist_delete(sqlist *l)
{
	/** free items memory block*/
	free(l->items);	
	/** free sqlist*/
	free(l);
}

//#define N 12
//
//static pitem_show pf = item_show;
//static pitem_equal pf1 = item_equal;
//
//static int A[4] = {3,5,8,11};
//static int B[7]={2,6,8,9,11,15,20};
//
//int main()
//{
//	sqlist *la, *lb;
//	
//	/** init sqlists*/
//	la = sqlist_new(N);
//	lb = sqlist_new(N);
//
//	/** enter items*/
//	sqlist_append_bulk(la, A, 4);
//	sqlist_append_bulk(lb, B, 7);
//
//	printf("la(%d) : ", la->length);
//	sqlist_show(la, pf);
//	printf("lb(%d) : ", lb->length);
//	sqlist_show(lb, pf);
//
//	printf("search 8 in la : %d \n", sqlist_search(la, 8, pf1));
//	printf("search 123 in la : %d \n", sqlist_search(la, 123, pf1));
//
//	sqlist_delete(la);
//	sqlist_delete(lb);
//}
