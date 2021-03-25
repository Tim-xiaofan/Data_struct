/** 20210323 22:37, zyj, GuangDong*/
//list.c
#include <stdlib.h>
#include <stdio.h>
#include "list.h"


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
list_get_n(const list *l, int i, item * e)
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
	item_assign(e, p->data);
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

	item_assign(&tmp->data, e);
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

bool 
list_append_bulk(list *l, const item *es, int n)
{
	int i;

	if(n > (l->size - l->length))
	{
		printf("not enough space.\n");
		return false;
	}

	for(i = 0; i < n; i++)
		list_append(l, es[i]);
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
		(*pf)(p->data);
		printf(" ");
		p = p->next;
	}
	printf("\n");
}

/** @return -1 indicates e is not in list , or return index*/
int 
list_search(const list *l, const item e, pitem_equal pf)
{
	int i;
	bool found;
	item e1;

	found = false;
	for(i = 0; i < l->length; i++)
	{
		list_get_n(l, i, &e1);
		if((*pf)(e, e1))
		{
			found = true;
			break;
		}
	}

	if(found) return i;
	else return -1;
}

/** do not attempt to access a list after deleting it.*/
void list_delete(list *l)
{
	node *p = l->head, *tmp;
	/** free nodes*/
	while(p)
	{
		tmp = p;
		p = p->next;
		free(tmp);
	}
	/** free list*/
	free(l);
}
