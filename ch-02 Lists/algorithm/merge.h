/** 20210327 19:31, zyj, GuangDong*/
//algoritm.h
#ifndef MERGE
#define MERGE
template <typename List>
void
Merge(const List & la, const List & lb, List & lc)
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
#endif
