/** 20210915, zyj, GuangDong*/
#ifndef _INSERT_SORT
#define _INSERT_SORT
#include <iostream>
using std::cout;
using std::endl;

#define RIGHT	true
#define LEFT	false

template<typename sqtable_t>
void move(sqtable_t & table, int start, int end)
{
	int k, len = table.length();

	for(k = end -1; k >= start && k < len; --k)
	  table[k + 1] = table[k];
}

template<typename sqtable_t>
void move(sqtable_t & table, int len, int start, int end, bool direction = RIGHT)
{
	int k;
	if(direction)
	{//右移
		for(k = end -1; k >= start && k < len; --k)
		  table[k + 1] = table[k];
	}
	else
	{
		// 7 , 8
		for(k = start - 1; k < end && k >= 0; ++k)
		{
			table[k] = table[k + 1];
		}
	}
}

template<typename D>
void show(const D & d, int len, int first, int last)
{
	int i = 0;

	for(i = first; i != last; i = (i + 1) % len)
	{
		if(i == 0) cout << "*";
		cout << d[i] << " ";
	}
	cout << endl;
}

/** O(n * n)*/
template<typename sqtable_t>
void insert_sort(sqtable_t & a, bool up = true)
{
    int len = a.length(), i = 1, j, k;
    typename sqtable_t::elem_type tmp;

    /** 跳过有序子序列*/
    while (i < len && a[i] > a[i -1]) ++i;
    for(; i < len; ++i)
    {
        if(a[i] >= a[i - 1]) continue;//已经是正确位置
        /** 寻找a[i]插入0...i-1位置*/
        for(j = 0; j < i - 1; ++j)
          if(a[i] < a[j]) break;
        tmp = a[i];
        for(k = i - 1; k >= j; --k) //move
          a[k + 1] = a[k];
        a[j] = tmp;
        cout << "insert " << tmp << " at " << j << ":";
        a.show();
    }
}

template<typename sqtable_t>
void binsert_sort(sqtable_t & table, bool up = true)
{
	int len = table.length(), i = 0, j , low = 0, high, mid;
	typename sqtable_t::elem_type tmp;

	while (i < len && table[i] > table[i -1]) ++i;
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

template<typename sqtable_t>
void twoway_insert_sort(sqtable_t & table, bool up = true)
{
    int len = table.length() + 1, i, j, k, first, last;
    typedef typename sqtable_t::elem_type elem_type;
    elem_type tmp, *d; 

    d = new elem_type[len];//循环辅助向量
    d[0] = table[0];  
    first =  0;
    last = 1;

    for(i = 1; i < table.length(); ++i)
    {
        tmp = table[i];
        if(tmp < d[0]) //插入到d[0]之前的有序序列
        {
            if(first == 0) 
            {
                d[len -1] = tmp;
                first = len -1;
            }
            else
            {
                for(j = len - 1; j >= first; --j) 
                  if(tmp > table[j]) break;//
                for(k = first; k <= j; ++k)
                  d[k - 1] = d[k];//fisrt...j左移
                d[j] = tmp; --first;
            }
        }
        else
        {
           for(j = 0; j < last; ++j) 
             if(tmp < table[j]) break;//
           for(k = last - 1; k >= j; --k)
             d[k + 1] = d[k];//fisrt...j右移
           d[j] = tmp; ++last;
        }
        cout << "after inserting (" << tmp<< "): ";
        show(d, len, first, last);
    }//for

    for(i = 0, j = first; j != last; ++i, j = (j + 1) %len)
        table[i] = d[j];
    delete [] d;
}

template<typename sqtable_t>
void show(sqtable_t & table, int dk, int start)
{
	int i, len = table.length();
	for(i = start; i < len ; i += dk)
	  cout << table[i] << " ";
	cout << endl;
}

/** 以start开始、增量为dk的子表的插入排序*/
template<typename sqtable_t>
void shell_insert(sqtable_t & table, int dk, int start)
{
	int i, j, k, len = table.length();
	typename sqtable_t::elem_type tmp;

	for(i = start + dk; i < len; i += dk)
	{
        if(table[i] >= table[i - dk]) continue;//已经是正确位置
		tmp = table[i];
		for(j = start; j < i; j += dk)//在有序表中寻找table[i]插入位置
			if(tmp < table[j]) break;

        for(k = i - dk; k >= j; k -= dk)//move
          table[k +  dk] = table[k];
        table[j] = tmp;
	}
}

/**
  对顺序表L作一次dk增量的希尔插入排序
 */
template<typename sqtable_t>
void shell_insert(sqtable_t & table, int dk)
{
	int i, len = table.length();

	for(i = 0; i < len; ++i)
	  shell_insert(table, dk, i);//子表i的插入排序
}

template<typename sqtable_t>
void shell_sort(sqtable_t & table, int dlta[], int t)
{
	int i;

	for(i = 0; i < t; ++i)
	{
		shell_insert(table, dlta[i]);//一趟增量为dlta[i]的插入排序
		cout << "after shell(" << i + 1 << ") : ";
		table.show();
	}
}

#endif
