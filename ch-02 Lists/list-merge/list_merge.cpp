/** 20210325 11:37, zyj, GuangDong*/
//list_merge.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "List.h"
#include "Merge.h"
#define N 12

static int A[4] = {3,5,8,11};
static int B[7]={2,6,8,9,11,15,20};

int main()
{
	//int i;
	List<int> la(N), lb(N), lc(N + N);
	
	/** enter items*/
	la.append_bulk(A, 4);
	lb.append_bulk(B, 7);

	printf("la(%d) : ", la.length());
	la.show();
	printf("lb(%d) : ", lb.length());
	lb.show();
	printf("lc(%d) : ", lc.length());
	lc.show();

	Merge(la, lb, lc);
	printf("after merging, lc(%d) : ", lc.length());
	lc.show();
}
