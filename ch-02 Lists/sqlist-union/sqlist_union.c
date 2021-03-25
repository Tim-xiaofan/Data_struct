/** 20210324 21:26, zyj, GuangDong*/
//list_union.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sqlist.h>
#define N 12

static pitem_show pf = item_show;
static pitem_equal pf1 = item_equal;

static int A[4] = {3,5,8,11};
static int B[7]={2,6,8,9,11,15,20};
static int C[N]={1,3,5,7,9,11,13,15,17,19,21,23};
static int D[N]={2,4,6,8,10,12,14,16,18,20,22,24};

static sqlist * 
sqlist_union(const sqlist *la, const sqlist *lb);

int main()
{
	//int i;
	sqlist *la, *lb, *lc, *ld, *ltmp;
	
	/** init sqlists*/
	la = sqlist_new(N);
	lb = sqlist_new(N);
	lc = sqlist_new(N);
	ld = sqlist_new(N);

	/** enter items*/
	//for(i = 0; i < 4; i++)
	//  sqlist_append(la, A[i]);
	sqlist_append_bulk(la, A, 4);
	//for(i = 0; i < 7; i++)
	//  sqlist_append(lb, B[i]);
	sqlist_append_bulk(lb, B, 7);
	sqlist_append_bulk(lc, C, N);
	sqlist_append_bulk(ld, D, N);

	printf("la(%d) : ", sqlist_length(la));
	sqlist_show(la, pf);
	printf("lb(%d) : ", sqlist_length(lb));
	sqlist_show(lb, pf);
	printf("lc(%d) : ", sqlist_length(lc));
	sqlist_show(lc, pf);
	printf("ld(%d) : ", sqlist_length(ld));
	sqlist_show(ld, pf);

	ltmp = sqlist_union(la, lb);
	printf("la U lb(%d) : ", sqlist_length(ltmp));
	sqlist_show(ltmp, pf);
	sqlist_delete(ltmp);
	ltmp = NULL;
	
	ltmp = sqlist_union(lc, ld);
	printf("lc U ld(%d) : ", sqlist_length(ltmp));
	sqlist_show(ltmp, pf);
	sqlist_delete(ltmp);
	ltmp = NULL;


	ltmp = sqlist_union(la, la);
	printf("la U la(%d) : ", ltmp->length);
	sqlist_show(ltmp, pf);
	sqlist_delete(ltmp);
	ltmp = NULL;
}	

static sqlist * 
sqlist_union(const sqlist *la, const sqlist *lb)
{
	sqlist *lc;
	item e;
	int i;

	lc = sqlist_new(N + N);
	/** lc = la */
	for(i = 0; i < la->length; i++)
	{
		sqlist_get_n(la, i, &e);
		sqlist_append(lc, e);
	}

	/** add items those are in lb but not in la to c */
	for(i = 0; i < lb->length; i++)
	{
		sqlist_get_n(lb, i, &e);
		/** test whether duplicated*/
		if(sqlist_search(la, e, pf1) == -1)
		  sqlist_append(lc, e);
	}

	//sqlist_show(lc, pf);
	return lc;
}
