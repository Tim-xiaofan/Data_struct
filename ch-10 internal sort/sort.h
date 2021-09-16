/** 20210915, zyj, GuangDong*/
#ifndef _SORT
#define _SORT
#include <iostream>
using std::cout;
using std::endl;

template<typename sqtable_t>
void move(sqtable_t & table, int start, int end)
{
	int k, len = table.length();

	for(k = end -1; k >= start && k < len; --k)
	  table[k + 1] = table[k];
}

/** O(n * n)*/
template<typename sqtable_t>
void insert_sort(sqtable_t & table, bool up = true)
{
	int len = table.length(), i, j, k;
	typename sqtable_t::elem_type tmp;

	if(up)
	{
		//cout << "enter insert_sort\n";
		//cout << "len : " << len << endl;
		i = 1;
		while (i < len && table[i] > table[i -1]) 
		{
			//cout << "i : " << i << endl;
			++i;
		}
		//cout << "i = " << i << endl;
		for(j = i; j < len; ++j)
		{
			tmp  = table[j];
			//insert into sorted[0...i-1] or append
			for(k = 0; k <= i && k < len; ++k)
			{
				if(k == 0)
				{
					if(tmp < table[k])//minimum
					{
						//cout << "k = " << k << endl;
						move(table, 0, j);
						table[0] = tmp;
						++i;
						break;
					}
				}
				else if(k == i)//maximum
				{
					//cout << "k = " << k << endl;
					move(table, k, j);
					table[k] = tmp;
					++i;
					break;
				}
				else
				{
					if(tmp >= table[k - 1] && tmp < table[k])
					{
						//cout << "k = " << k << endl;
						move(table, k, j);
						table[k] = tmp;
						++i;
						break;
					}
				}
			}
			cout << "after inserting " << tmp << ": ";
			table.show();
		}
	}
}

template<typename sqtable_t>
void binsert_sort(sqtable_t & table, bool up = true)
{
	int len = table.length(), i, j , low = 0, high, mid;
	typename sqtable_t::elem_type tmp;

	if(up)
	{
		//cout << "enter insert_sort\n";
		//cout << "len : " << len << endl;
		i = 1;
		while (i < len && table[i] > table[i -1]) 
		{
			//cout << "i : " << i << endl;
			++i;
		}
		//cout << "i = " << i << endl;
		for(j = i; j < len; ++j)
		{
			tmp  = table[j];
			high = i - 1;
			low = 0;
			while(low <= high)
			{
				mid = (low + high) / 2;
				if(tmp < table[mid]) high = mid -1;
				else low = mid + 1;
			}
			cout << "high + 1 = " << high + 1 << " : "; 
			move(table, high + 1, i);
			table[high + 1] = tmp;
			++i;
			cout << "after inserting " << tmp << ": ";
			table.show();
		}
	}
}

#endif
