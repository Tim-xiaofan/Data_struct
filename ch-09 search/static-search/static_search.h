/**20210907, zyj, GuangDong*/
#ifndef _STATIC_SEARCH
#define _STATIC_SEARCH

template<typename T>
bool eq(const T & a, const T & b)
{
    return (a == b);
}

template<typename T>
int cmp(const T & a, const T & b)
{
    if(a < b) return -1;
    if(a == b) return 0;
    if(a > b) return 1;
	return -1;
}

/**
 * return : -1 for not found, > -1 for location
 * 适用:线性表
 * */
template <typename LTable, typename EQ>
int sq_search(const LTable & table, 
            const typename LTable::elem_type & e,
            const EQ & eq)
{
    int i;
    typename LTable::const_iterator it;

    for(it = table.begin(), i = 0; it != table.end(); ++it, ++i)
      if(eq(*it, e)) return i;
    return -1;
}

/**
	binary search : sorted and sq-memory table
 */

template <typename SQTable, typename Cmp>
int bin_search(const SQTable & table, 
            const typename SQTable::elem_type & e,
			const Cmp & cmp)
{
	int low = 0, mid, high = table.size() - 1;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(cmp(table[mid], e) == 0) return mid;
		if(cmp(e, table[mid]) > 0) // find in right
		  low = mid + 1;
		else //find in left
		  high = mid -1;
	}
	return -1;
}

#endif
