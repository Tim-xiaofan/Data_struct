/** 20210323 22:25, zyj, GuangDong*/
//list.h
#ifndef LIST_H
#define LIST_H

typedef int item;

void item_assign(item *i1, const item *i2);

short item_compare(const item *i1, const item *i2);

struct NODE
{
	item data;
	struct NODE *next;
};

typedef struct NODE node;

struct LIST
{
	unsigned int length;
	node *head;
	node *tail;
};

typedef struct LIST list;

void list_init(list * l);

void list_get(list *l, unsigned int i, item * e);

void list_put(list *l, unsigned int i, item e);

unsigned int list_length(const list *l);

#endif
