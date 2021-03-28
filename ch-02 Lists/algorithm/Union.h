/** 20210324 21:26, zyj, GuangDong*/
//Union.h -- get collection of two lists
#ifndef UNION_H
#define UNION_H
#include <iostream>

template<class List> 
bool
Union(const List & la, const List & lb, List & lc)
{
	class List::input_iterator it;

	/** self union*/
	if(&la == &lb)
	{
		if(&lc == &la) /** target list is la self */
		  return true;
		else
		{
			if(lc.size() < (la.length()))
			  return false;
			/** lc = la */
			for(it = la.begin(); it != la.end(); ++it)
			  lc.append(*it);
			return true;
		}
	}
	else
	{
		if(&lc == &la)
		{/** target list is la*/
			if(la.size() < la.length() + lb.length())
			  return false;
			/** add items those are in lb but not in la to lc */
			for(it = lb.begin(); it != lb.end(); ++it)
			{
				/** test whether duplicated*/
				if(lc.search(*it) == -1)
				  lc.append(*it);
			}

		}
		else if(&lc == &lb) 
		{/** target list is lb*/
			if(lb.size() < lb.length() + la.length())
			  return false;
			/** add items those are in la but not in lb to lc */
			for(it = la.begin(); it != la.end(); ++it)
			{
				/** test whether duplicated*/
				if(lc.search(*it) == -1)
				  lc.append(*it);
			}
			return true;
		}
		else
		{/** target list is lc*/
			if(lc.size() < (la.length() + lb.length()))
			  return false;
			/** lc = la */
			for(it = la.begin(); it != la.end(); ++it)
			  lc.append(*it);

			/** add items those are in lb but not in la to c */
			for(it = lb.begin(); it != lb.end(); ++it)
			{
				/** test whether duplicated*/
				if(lc.search(*it) == -1)
				  lc.append(*it);
			}
			return true;
		}	
	}
	//list_show(lc, pf);
	return true;
}
#endif
