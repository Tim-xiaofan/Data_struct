/**20210907, zyj, GuangDong*/
#ifndef _STATIC_SEARCH
#define _STATIC_SEARCH

template<typename T>
bool find(const T & a, const T & b)
{
    return (a == b);
}

/**
 * return : -1 for not found, > -1 for location
 * */
template <typename SQTable, typename Find>
int sq_search(const SQTable & table, 
            const typename SQTable::elem_type & e,
            const Find & find)
{
    int i;
    typename SQTable::const_iterator it;

    for(it = table.begin(), i = 0; it != table.end(); ++it, ++i)
      if(find(*it, e)) return i;
    return -1;
}

#endif
