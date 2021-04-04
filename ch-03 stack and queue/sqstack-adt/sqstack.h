/** 20210401 21:44, zyj, GuangDong*/
#ifndef SQSTACK_H
#define SQSTACK_H
#include <iostream>
#include "../../ch-02 linear lists/sqlist-adt/SqList.h"

template <typename Item>
class sqstack : private SqList<Item>
{
	private:
		typedef SqList<Item> base; 
	private:
		enum {default_size = 512};
	public:
		~sqstack(){};
		sqstack(int size = default_size): base(size){};
		sqstack(const Item * is, int n): base(is, n){};
		sqstack(const sqstack & st): base(st){};
		sqstack & operator=(const sqstack &) = delete;
		/** read top item*/
		void get_top(Item & i)const{i = base::operator[](base::length()-1);};
		bool push(const Item & i){return base::append(i);}
		/** read top item and delete it*/
		bool pop(Item & i){return base::del_n(base::length()-1, i);}
		bool is_empty(void)const{return base::is_empty();};
		bool is_full(void)const{ return base::is_full();};
		void show(void)const{base::show();};
		int length(void)const{return base::length();}
		int size(void)const{return base::size();}
		/** random access*/
		const Item & operator[](int i){return base::operator[](i);}
};
#endif