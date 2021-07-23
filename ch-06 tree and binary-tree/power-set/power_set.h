/** 20210723 12:38, zyj, GuangDong*/
//power_set.h -- power_set
#ifndef _POWER_SET_H
#define _POWER_SET_H
#include <iostream>
#include <cstring>

using std::cout;
using std::cerr;
using std::endl;

template <typename Data>
class power_set
{
	private:
		int size;
		List<Data> set;
	public:
		~power_set(){}
		power_set(): size(0), set(0){}
		power_set(const List<Data> & set);
};

template <typename Data>
power_set<Data>::
power_set(const List<Data> & set)
{
}

#endif
