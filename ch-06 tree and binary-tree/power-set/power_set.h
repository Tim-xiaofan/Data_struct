/** 20210723 12:38, zyj, GuangDong*/
//power_set.h -- power_set
#ifndef _POWER_SET_H
#define _POWER_SET_H
#include <iostream>
#include <cstring>
#include "List.h"

using std::cout;
using std::cerr;
using std::endl;

template <typename Data>
class power_set
{
	private:
		int _n, _size;//原集合元素个数
		List<List<Data>> _set;
	public:
		~power_set(){}
		power_set(): _n(0),_size(0), _set(0){}
		power_set(const List<Data> & set);
	private:
		void power(int i, const List<Data> & A, List<Data> & B);
};

template <typename Data>
power_set<Data>::
power_set(const List<Data> & set):
	_n(set.length()), _size(1 << _n), _set(_size)
{
	List<Data> B(_n);
	power(0, set, B);
}


/**
  @param    n   当前层数
  @param    A   元集合
  @param    B   幂集
 */

template <typename Data>
void power_set<Data>::
power(int i, const List<Data> & A, List<Data> & B)
{
	int k, deta, j;
	Data x, y;
	if(i >= _n) 
	{
		B.show();
	}
	else
	{
		A.get_n(i, x);
		k = B.length();
		B.append(x);//取第i个元素

		power(i + 1, A, B);
		deta = B.length() - k;
		for(j = 0; j < deta; ++j)
		{//移除余下的元素
			B.del_n(B.length() - 1, y);
		}
		power(i + 1, A, B);//不取第i个元素
	}
}

#endif
