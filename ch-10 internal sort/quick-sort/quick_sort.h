/** 20210918, zyj, GuangDong*/
#ifndef _QUICK_SORT
#define _QUICK_SORT
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

template<typename sqtable_t>
void bubble_sort(sqtable_t & table, bool up = true)
{
	int i, j, len = table.length();
	typename sqtable_t::elem_type tmp;
	bool swapped;

	if(!up) return;/** TODO : down sort*/

	for(i = 0; i < len - 1; ++i)// 第i轮排序, 最多n-1轮(逆序)
	{
		swapped = false;
		for(j = 0; j < len - i - 1; j++)// [0--len -i)冒泡
		  if(table[j] > table[j + 1])
		  {
			  tmp = table[j];
			  table[j] = table[j + 1];
			  table[j + 1] = tmp;
			  swapped = true;
		  }
		if(!swapped) break;//一次交换都没有发生
	}
}


template<typename sqtable_t>
int quick_partition(sqtable_t & table, int low, int high)
{
	//int len = table.length();
	typename sqtable_t::elem_type pivot;

	pivot = table[low];
	while(low < high)
	{
		while(low < high && table[high] > pivot) --high;
		table[low] = table[high];
		while(low < high && table[low] < pivot) ++low;
		table[high] = table[low];
	}
	table[low] = pivot;
	return low;
}

template<typename sqtable_t>
void quick_sort(sqtable_t & table, int low, int high)
{
	int pivot;
	if(low < high)
	{
		pivot = quick_partition(table, low, high);
		quick_sort(table, low, pivot -1);
		quick_sort(table, pivot + 1, high);
	}
}

template<typename sqtable_t>
void quick_sort(sqtable_t & table)
{
	quick_sort(table, 0, table.length() -1);
}
#endif
