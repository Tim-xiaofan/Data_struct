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
		int _n, _size;
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
	//cout << "_n = " << _n
	//	<< ", _size = " << _size << endl;
	List<Data> B(_n);
	power(0, set, B);
}

template <typename Data>
void power_set<Data>::
power(int i, const List<Data> & A, List<Data> & B)
{
	//static int index = 0;
	int k, deta, j;
	Data x, y;
	if(i >= _n) 
	{
		//cout << "#-" << index++ << "*******P(A) : ";
		B.show();
		//_set.append(B);
	}
	else
	{
		A.get_n(i, x);
		k = B.length();
		//cout << "before append , length = " << B.length() << ", ";
		//B.show();
		//cout << "k = " << k 
		//	<< ", x = " << x << endl;
		B.append(x);
		//cout << "after append , length = " << B.length() << ", ";
		//B.show();

		power(i + 1, A, B);
		deta = B.length() - k;
		//cout << "deta = " << deta << endl;
		//cout << "len = " << B.length() << endl;
		//cout << "#1 : "; B.show();
		for(j = 0; j < deta; ++j)
		{
			//cout << "before deleting , length = " << B.length() << ", ";
			//B.show();
			B.del_n(B.length() - 1, y);
			//cout << "del : y = " << y << endl;
			//cout << "after deleting , length = " << B.length() << ", ";
			//B.show();
		}
		//cout << "len = " << B.length() << endl;
		//cout << "#2 : "; B.show();
		power(i + 1, A, B);
		//cout << "len = " << B.length() << endl;
		//cout << "#3 : "; B.show();
	}
}

#endif
