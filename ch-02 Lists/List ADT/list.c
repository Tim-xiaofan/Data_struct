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

short 
item_compare(const item *e1, const item *e2)
{
	if(*e1 > *e2) return 1;
	if(*e1 == *e2) return 0;
	return -1;
}

void
item_show(const item * e)
{
	printf("%d", *e);
}

list* 
list_new(int size)
{
	list *l;
	l = (list *)malloc(sizeof(list));
	if(l == NULL)
	{
		printf("can not alloc buffer for list\n");
		return NULL;
	}
	l->length = 0;
	l->size = size;
	l->head = (node *)malloc(sizeof(node));
	l->head->next = l->tail = NULL;
	return l;
}

bool
list_get_n(list *l, int i, item * e)
{
	int j;
	node *p;

	if(l->length == 0) 
		return false;
	if(i >= l->length || i < 0)
	{
		printf("out of boundary\n");
		return false;
	}

	p = l->head->next;
	for(j = 0; j < i; j++)
	  p = p->next;
	item_assign(e, &p->data);
	return true;
}

bool 
list_append(list *l, item e)
{
	if(l->length == l->size)
	{
		printf("list is full\n");
		return false;
	}

	node *tmp;
	tmp = (node *) malloc(sizeof(node));
	if(tmp == NULL)
	{
		printf("can not alloc buffer\n");
		return false;
	}

	item_assign(&tmp->data, &e);
	tmp->next = NULL;
	/** 0 --> 1*/
	if(l->length == 0)
	{
		l->head->next = tmp;
		l->tail = tmp;
		l->length++;
	}
	else
	{/** n --> n + 1*/
		l->tail->next = tmp;;
		l->tail = tmp;
		l->length++;
	}
	return true;
}

int 
list_length(const list *l)
{
	return l->length;
}


void list_show(const list *l, pitem_show pf)
{
	node *p;

	if(l->length == 0)
	{
		printf("empty list");
		return;
	}

	p = l->head->next;
	while(p != NULL)
	{
		(*pf)(&p->data);
		printf(" ");
		p = p->next;
	}
	printf("\n");
}
