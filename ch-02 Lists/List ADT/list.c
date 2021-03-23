/** 20210323 22:37, zyj, GuangDong*/
//list.c
#include <stdlib.h>
#include <stdio.h>
#include "list.h"


void 
item_assign(item *e1, const item *e2)
{
	*e1 = *e2;
}

void 
list_init(list * l)
{
	l->length = 0;
	l->head = l->tail = NULL;
}

void 
list_get(list *l, unsigned int i, item * e)
{
}

void 
list_put(list *l, unsigned int i, item e)
{
	node *tmp;
	tmp = (node *) malloc(sizeof(node));
	if(tmp == NULL)
	{
		printf("can not alloc buffer\n");
		exit(-1);
	}

	item_assign(&tmp->data, &e);
}

unsigned int 
list_length(const list *l)
{
	return 0;
}
