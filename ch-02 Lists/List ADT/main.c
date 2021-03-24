/** 20210323 22:37, zyj, GuangDong*/
//list.c
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"
#define N 12
#define M 1000

pitem_show pf = item_show;

int main()
{
	srand(time(NULL));

	list *l = NULL;
	l = list_new(N);
	while(list_append(l, 1 + rand() % M));
	list_show(l, pf);
	printf("length = %d\n", list_length(l));

	item e;
	int i;
	for(i = 0; i < list_length(l); i++)
	{
		list_get_n(l, i, &e);
		pf(&e);
		printf(" ");
	}
	printf("\n");

	list_get_n(l, 12, &e);
	list_get_n(l, -1, &e);
	return 0;
}
