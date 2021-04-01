/** 20210324 21:26, zyj, GuangDong*/
//list_union.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "List.h"
#include "Union.h"
#define N 12

static int A[4] = {3,5,8,11};
static int B[7]={2,6,8,9,11,15,20};
static int C[N]={1,3,5,7,9,11,13,15,17,19,21,23};
static int D[N]={2,4,6,8,10,12,14,16,18,20,22,24};

int main()
{
	List<int> la, lb, lc, ld, ltmp(2 * N);
	
	/** enter items*/
	la.append_bulk(A, 4);
	lb.append_bulk(B, 7);
	lc.append_bulk(C, N);
	ld.append_bulk(D, N);

	printf("la(%d) : ", la.length());
	la.show();
	printf("lb(%d) : ", lb.length());
	lb.show();
	printf("lc(%d) : ", lc.length());
	lc.show();
	printf("ld(%d) : ", ld.length());
	ld.show();

	Union(la, lb, ltmp);
	printf("la U lb(%d) : ", ltmp.length());
	ltmp.show();
	
	ltmp.clear();
	Union(lc, ld, ltmp);
	printf("lc U ld(%d) : ", ltmp.length());
	ltmp.show();
	
	//ltmp.clear();
	Union(la, la, la);
	printf("la U la(%d) : ", la.length());
	la.show();
	
	Union(la, lb, la);
	printf("la U lb(%d) : ", la.length());
	la.show();
}	
