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

struct SQLIST
{
	int length;/** items count*/
	int size;/** memory block size*/
	item *items;/** base address*/
};

typedef struct SQLIST sqlist;

sqlist *sqlist_new(int size);

bool sqlist_get_n(const sqlist *sql, int i, item * e);

bool sqlist_remove_n(sqlist *sql, int i, item * e);

bool sqlist_insert_n(sqlist *sql, int i, item e);

bool sqlist_append(sqlist *sql, item e);

bool sqlist_append_bulk(sqlist *sql, const item *es, int n);

static inline int 
sqlist_length(const sqlist *sql) {return sql->length;}

void sqlist_show(const sqlist *sql, pitem_show pf);

int sqlist_search(const sqlist *sql, item e, pitem_equal pf);

void sqlist_delete(sqlist *sql);
#endif
