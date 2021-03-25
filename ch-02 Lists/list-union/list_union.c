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
static int C[N]={1,3,5,7,9,11,13,15,17,19,21,23};
static int D[N]={2,4,6,8,10,12,14,16,18,20,22,24};

static list * 
list_union(const list *la, const list *lb);

int main()
{
	int i;
	list *la, *lb, *lc, *ld, *ltmp;
	item e;
	
	/** init lists*/
	la = list_new(N);
	lb = list_new(N);
	lc = list_new(N);
	ld = list_new(N);

	/** enter items*/
	//for(i = 0; i < 4; i++)
	//  list_append(la, A[i]);
	list_append_bulk(la, A, 4);
	//for(i = 0; i < 7; i++)
	//  list_append(lb, B[i]);
	list_append_bulk(lb, B, 7);
	list_append_bulk(lc, C, N);
	list_append_bulk(ld, D, N);

	printf("la(%d) : ", la->length);
	list_show(la, pf);
	printf("lb(%d) : ", lb->length);
	list_show(lb, pf);
	printf("lc(%d) : ", lc->length);
	list_show(lb, pf);
	printf("ld(%d) : ", ld->length);
	list_show(ld, pf);

	ltmp = list_union(la, lb);
	printf("la U lb(%d) : ", ltmp->length);
	list_show(ltmp, pf);
	list_delete(ltmp);
	ltmp = NULL;
	
	ltmp = list_union(lc, ld);
	printf("lc U ld(%d) : ", ltmp->length);
	list_show(ltmp, pf);
	list_delete(ltmp);
	ltmp = NULL;


	ltmp = list_union(la, la);
	printf("la U la(%d) : ", ltmp->length);
	list_show(ltmp, pf);
	list_delete(ltmp);
	ltmp = NULL;

	printf("selet an item to rm in lb : ");
	scanf("%d", &i);
	list_remove_n(lb, i, &e);
	printf("after removing %d, lb(%d) : ",
				i, list_length(lb));
	list_show(lb, pf);


	printf("selet an location to insert into lb : ");
	scanf("%d", &i);
	list_insert_n(lb, i, 255);
	printf("after inserting %d, lb(%d) : ",
				i, list_length(lb));
	list_show(lb, pf);
}	

static list * 
list_union(const list *la, const list *lb)
{
	list *lc;
	item e;
	int i;

	lc = list_new(N + N);
	/** lc = la */
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
