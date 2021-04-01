/** 20210327 19:31, zyj, GuangDong*/
//algoritm.h
#ifndef ALGORITHN_H
#define ALGORITHN_H
template<class List>
bool
Merge(const List & la, const List & lb,  List & lc)
{
	typename List::input_iterator ita, itb;

	ita = la.begin();
	itb = lb.begin();
	if(lc.size() < la.size() + lb.size())
	  return false;

	/** both la and lb are not empty*/
	while((ita != la.end()) && (itb != lb.end()))
	{
		if(*ita < *itb)
		{
			lc.append(*ita);
			++ita;
		}
		else if(*ita == *itb)
		{
			lc.append(*ita);
			++ita;
			lc.append(*itb);
			++itb;
		}
		else
		{
			lc.append(*itb);
			++itb;
		}
	}

	/** merge remaing items in list A or B*/
	while(ita != la.end())
	{
		lc.append(*ita);
		++ita;
	}

	while(itb != lb.end())
	{
		lc.append(*itb);
		++itb;
	}

	return true;
}
#endif
