/** 20210324 21:26, zyj, GuangDong*/
//list_union.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <list.h>
#define N 12

static pitem_show pf = item_show;
static pitem_equal pf1 = item_equal;

static int A[4] = {3,5,8,11};
static int B[7]={2,6,8,9,11,15,20};

static list * 
list_union(const list *la, const list *lb);

int main()
{
	int i;
	list *la, *lb, *lc;
	
	/** init lists*/
	la = list_new(N);
	lb = list_new(N);

	/** enter items*/
	for(i = 0; i < 4; i++)
	  list_append(la, A[i]);
	for(i = 0; i < 7; i++)
	  list_append(lb, B[i]);

	printf("la(%d) : ", la->length);
	list_show(la, pf);
	printf("lb(%d) : ", lb->length);
	list_show(lb, pf);

	lc = list_union(la, lb);
	printf("la U lb(%d) : ", lc->length);
	list_show(lc, pf);
}	

static list * 
list_union(const list *la, const list *lb)
{
	list *lc;
	item e;
	int i;

	lc = list_new(N + N);
	/** lc = la*/
	for(i = 0; i < la->length; i++)
	{
		list_get_n(la, i, &e);
		list_append(lc, e);
	}

	/** add items those are in lb but not in la to c */
	for(i = 0; i < lb->length; i++)
	{
		list_get_n(lb, i, &e);
		/** test whether duplicated*/
		if(list_search(la, e, pf1) == -1)
		  list_append(lc, e);
	}

	//list_show(lc, pf);
	return lc;
}
