/** 20210323 22:25, zyj, GuangDong*/
//list.h
#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

typedef int item;

void item_assign(item *e1, const item *e2);

short item_compare(const item *e1, const item *e2);

void item_show(const item *e);

/** function pointer*/
typedef void (*pitem_show)(const item *);

struct NODE
{
	item data;
	struct NODE *next;
};

typedef struct NODE node;

struct LIST
{
	int length;
	int size;
	node *head;
	node *tail;
};

typedef struct LIST list;

list *list_new(int size);

bool list_get_n(list *l, int i, item * e);

bool list_append(list *l, item e);

int list_length(const list *l);

void list_show(const list *l, pitem_show pf);
#endif
