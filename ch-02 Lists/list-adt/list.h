/** 20210323 22:25, zyj, GuangDong*/
//list.h
#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

typedef int item;

item * item_new(void);

void item_delete(item * e);

void item_assign(item *e1, item e2);

short item_compare(item e1, item e2);

bool item_le(item e1, item e2);

bool item_equal(item e1, item e2);

void item_show(item e);

/** function pointer*/
typedef void (*pitem_show)(item );
typedef bool (*pitem_equal)(item e1, item e2);

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

bool list_get_n(const list *l, int i, item * e);

bool list_remove_n(list *l, int i, item * e);

bool list_insert_n(list *l, int i, item e);

bool list_append(list *l, item e);

bool list_append_bulk(list *l, const item *es, int n);

static inline int 
list_length(const list *l){return l->length;}

void list_show(const list *l, pitem_show pf);

int list_search(const list *l, item e, pitem_equal pf);

void list_delete(list *l);

static inline bool
list_isfull(const list *l){ return (l->length == l->size);}
#endif
