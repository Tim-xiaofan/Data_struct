/** 20210405 18:38, zyj, GuangDong*/
#ifndef LINKQUEUE_H
#define LINKQUEUE_H
#include <iostream>
#include "List.h"

template <typename Item>
class linkqueue : private List<Item>
{
	private:
		typedef List<Item> base;
		enum{default_size = 512};
	public:
		typedef Item value_type;
	public:
		linkqueue(int size = default_size):base(size){}
		bool enqueue(const Item & i){return base::append(i);}
		bool dequeue(Item & i){return base::del_n(0, i);}
		bool get_top(Item & i)const {return base::back(i);}
		int length(void)const{return base::length();}
		int size(void)const{return base::size();}
		bool is_full(void)const {return base::is_full();}
		bool is_empty(void)const {return base::is_empty();}
		void show(void)const {base::show();}
};
#endif
