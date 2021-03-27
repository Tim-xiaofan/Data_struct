/** 20210325 11:37, zyj, GuangDong*/
//list_merge.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <list.h>
#define N 12

static int A[4] = {3,5,8,11};
static int B[7]={2,6,8,9,11,15,20};

static bool
merge(const List & la, const List &lb, List &lc);

int main()
{
	//int i;
	List la(N), lb(N), lc(N + N);
	
	/** enter items*/
	la.append_bulk(A, 4);
	lb.append_bulk(B, 7);

	printf("la(%d) : ", la.length());
	la.list_show();
	printf("lb(%d) : ", lb.length);
	lb.list_show();

	merge(la, lb, lc);
	printf("merge(%d) : ", lc.length());
	lc.show();
}

static bool
list_merge(const List & la, const List &lb, List &lc)
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
