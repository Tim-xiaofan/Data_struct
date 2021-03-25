/** 20210325 11:37, zyj, GuangDong*/
//list_merge.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <list.h>
#define N 12

static pitem_show pf = item_show;
//static pitem_equal pf1 = item_equal;

static int A[4] = {3,5,8,11};
static int B[7]={2,6,8,9,11,15,20};

static list *
list_merge(const list *la, const list *lb);

int main()
{
	//int i;
	list *la, *lb, *lc;
	
	/** init lists*/
	la = list_new(N);
	lb = list_new(N);

	/** enter items*/
	list_append_bulk(la, A, 4);
	list_append_bulk(lb, B, 7);

	printf("la(%d) : ", la->length);
	list_show(la, pf);
	printf("lb(%d) : ", lb->length);
	list_show(lb, pf);

	lc = list_merge(la, lb);
	printf("merge(%d) : ", list_length(lc));
	list_show(lc, pf);

	list_delete(la);
	list_delete(lb);
	list_delete(lc);
}

static list *
list_merge(const list *la, const list *lb)
{
	item ea, eb;
	list *lc;
	int ia = 0, ib = 0, lena, lenb;
	short ret = 0;

	lena = list_length(la); 
	lenb = list_length(lb);
	lc = list_new(lena + lenb);

	/** both la and lb are not empty*/
	while((ia < lena) && (ib < lenb))
	{
		if(ret <= 0)list_get_n(la, ia, &ea);
		if(ret >= 0)list_get_n(lb, ib, &eb);

		//printf("choose among : ");
		//item_show(ea);
		//printf(" ");
		//item_show(eb);
		//printf("\n");
		ret = item_compare(ea, eb);

		if(ret < 0)
		{
			//printf("choose : ");
			//item_show(ea);
			//printf("\n");
			list_append(lc, ea);
			ia++;
		}
		else if(ret == 0)
		{
			list_append(lc, ea);
			ia++;
			list_append(lc, eb);
			ib++;
		}
		else 
		{
			//printf("choose : ");
			//item_show(eb);
			//printf("\n");
			list_append(lc, eb);
			ib++;
		}
	}

	/** merge remaing items in list A or B*/
	while(ia < lena)
	{
		list_get_n(la, ia++, &ea);
		list_append(lc, ea);
	}

	while(ib < lenb)
	{
		list_get_n(lb, ib++, &eb);
		list_append(lc, eb);
	}

	return lc;
}
