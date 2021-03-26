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

static node *
list_locate_n(const list *l, int n)
{
	node *p;
	int j;

	p = l->head;
	for(j = 0; j <= n; j ++)
	  p = p->next;

	return p;
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
	l->current = -1;
	l->cursor = l->head;
	return l;
}

/** set cursor
 *	O(n)*/
bool 
list_set_cursor(list* l, int i)
{
	int len ;
	node *p;

	len = list_length(l);
	if(i >= len)
	  return false;

	p = list_locate_n(l, i);
	l->cursor = p;
	l->current = i;

	fprintf(stdout, 
				"set cursor to location %d, data is", 
				l->current);
	item_show(l->cursor->data);
	printf("\n");

	return true;
}

bool 
list_reset_cursor(list *l)
{
	return list_set_cursor(l, -1);
}

/** O(1)
 *	@return -1 for failed, or current location 
 *	after calling this function
 **/
int 
list_get_next(list *l, item *e)
{
	if(l->current < list_length(l) -1)
	{
		l->current++;
		l->cursor = l->cursor->next;
		item_assign(e, l->cursor->data);
		return l->current;
	}
	if(l->current == list_length(l) -1)
		item_assign(e, l->cursor->data);
	return -1; 
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



/** O(n)*/
bool 
list_remove_n(list *l, int i, item * e)
{
	node *p, *tmp;
	int len = list_length(l), j;

	if(i < 0 || i >= len)
	{
		fprintf(stderr, "out of boundary\n");
		return false;
	}

	/** 1--> 0 */
	if(len == 1)
	{
		item_assign(e, l->tail->data);
		free(l->tail);
		l->tail = NULL;
		l->head->next = l->tail;
	}
	else
	{/** n --> n - 1*/
		/** locate to i-1*/
		p = l->head;
		for(j = 0; j < i; j ++)
		  p = p->next;

		/** = operator*/
		tmp = p->next;
		item_assign(e, tmp->data);
		//fprintf(stdout, "rm item : ");
		//item_show(*e);
		//fprintf(stdout, "\n");

		/** adjust and free node*/
		p->next = tmp->next;
		free(tmp);
	}

	l->length--;
	return true;
}

/** O(n)*/
bool 
list_insert_n(list *l, int i, item e)
{
	int len;
	node *tmp, *p;

	len = list_length(l);

	if(list_isfull(l))
	{
		fprintf(stderr, "list is full\n");
		return false;
	}

	if(i < 0 || i > len)
	{
		fprintf(stderr, "out of boundary\n");
		return false;
	}

	tmp = (node *) malloc(sizeof(node));
	if(!tmp)
	{
		fprintf(stderr, "failed to alloc buffer for node\n");
		return false;
	}
	item_assign(&tmp->data, e);
	tmp->next = NULL;

	/** 0 --> 1*/
	if(len == 0)
	{
		l->tail = tmp;
		l->head->next = l->tail;
	}
	else
	{/** n --> n + 1*/
		/** locate i - 1*/
		p = list_locate_n(l, i - 1);
		tmp->next = p->next;
		p->next = tmp;
	}
	l->length++;
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
