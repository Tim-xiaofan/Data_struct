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
	{
		for(k = end -1; k >= start && k < len; --k)
		  table[k + 1] = table[k];
	}
	else
	{
		// 7 , 8
		for(k = start - 1; k < end && k >= 0; ++k)
		{
			//cout << "move: " << "d[" << k <<"] = " << table[k]
			//	<< "<-----" << "d[" << k + 1<< "] = " << table[k +1] << endl;
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

template<typename sqtable_t>
void twoway_insert_sort(sqtable_t & table, bool up = true)
{
	int length = table.length(), i, j, first, last, len;
	typedef typename sqtable_t::elem_type elem_type;
	elem_type tmp, *d; 

	len = length + 1;
	d = new elem_type[len];
	d[0] = table[0];  
	first =  0;
	last = 1;

	if(up)
	{
		for(i = 1; i < length; ++i)
		{
			tmp = table[i];
			if(tmp < d[0]) // front insert
			{
				//cout << "**front insert("<< tmp<< ")" << endl;
				if(first == 0)
				{
					first = len - 1;
					d[first] = tmp;
				}
				else
				{
					if(tmp >= d[len - 1])//maximum
					{
						//cout << "maximum\n";
						//cout << "first : " << first << endl;
						//cout << "len -1 : " << len -1 << endl;
						move(d, len, first, len -1, LEFT);
						--first;
						d[len -1] = tmp;
					}
					else if(tmp < d[first])//minimum
					{
						//cout <<"minimum\n";
						d[--first] = tmp;
					}
					else
					{
						//cout <<"medimum\n";
						for(j = first; j < len; ++j)
						{
							if(d[j] <= tmp && tmp < d[j +1])
							{
								move(d, len, first, j, LEFT);
								--first;
								d[j] = tmp;
								break;
							}
						}
					}
				}
			}
			else
			{
				//cout << "**behand insert("<< tmp<< ")" << endl;
				if(last == 1)
				{
					d[last++] = tmp;
				}
				else
				{
					if(tmp < d[1])//minimum
					{
						//cout << "minimum\n";
						move(d, len, 1, last, RIGHT);
						++last;
						d[1] = tmp;
					}
					else if(tmp >= d[last -1])//maximum
					{
						//cout << "maximum\n";
						d[last++] = tmp;
					}
					else
					{
						//cout << "medimum\n";
						for(j = 1; j < last; ++j)
						{
							if(d[j] <= tmp && tmp < d[j +1])
							{
								//cout << "j = " << j << endl;
								move(d, len, j + 1, last, RIGHT);
								++last;
								d[j + 1] = tmp;
								break;
							}
						}
					}
				}
			}
			//cout << "first : " << first << endl;
			//cout << "last : " << last << endl;
			cout << "after inserting (" << tmp<< "): ";
			show(d, len, first, last);
		}//for
		//cout << "finish : ";
		//show(d, len, first, last);

		for(i = 0, j = first; i < length && j != last; ++i, j = (j + 1) %len)
		{
			table[i] = d[j];
		}
	}
}

template<typename sqtable_t>
void show(sqtable_t & table, int dk, int start)
{
	int i, len = table.length();
	for(i = start; i < len ; i += dk)
	  cout << table[i] << " ";
	cout << endl;
}

template<typename sqtable_t>
void shell_insert(sqtable_t & table, int dk, int start, bool up = true)
{
	int i = 0, j, k, l, len = table.length();
	typename sqtable_t::elem_type tmp;
	int count = (len - 1 - start) / dk;
	//int end = count * dk + start;
	//cout << "****" << endl;
	//cout << "start=" << start;
	//cout << ", end=" << end;
	//cout << ", len=" << len;
	//cout << ", dk=" << dk;
	//cout << ", count=" << count << ": ";
	//show(table, dk, start);

	if(!up) return;

	while(i < count)
	{
		j = start + (i + 1) * dk;//有序表的后一个节点
		tmp = table[j];
		for(k = start; k < j; k += dk)//在有序表中寻找插入位置
		{
			if(tmp < table[k])//insert into location k
			{
				for(l = j; l > k; l-=dk)//move
				  table[l] = table[l - dk];
				table[k] = tmp;
				break;
			}
		}
		++i;
		//cout << "after inserting("<< tmp <<") : ";
		//show(table, dk, start);
		//table.show();
	}
}

/**
  对顺序表L作一次希尔插人排序
 */
template<typename sqtable_t>
void shell_insert(sqtable_t & table, int dk,  bool up = true)
{
	int i, len = table.length();

	for(i = 0; i < len - dk; ++i)
	  shell_insert(table, dk, i, up);//子表i的插入排序
}

template<typename sqtable_t>
void shell_sort(sqtable_t & table, int dlta[], int t, bool up = true)
{
	int i;

	for(i = 0; i < t; ++i)
	{
		//cout << "--------------" << i << "-------------" << endl;
		shell_insert(table, dlta[i], up);//一趟增量为dlta[i]的插入排序
		cout << "after shell(" << i + 1 << ") : ";
		table.show();
	}
}
#endif
