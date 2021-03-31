/** 20210330 20:54, zyj, GuangDong*/
//Polymial.h
#ifndef POLYMIAL_H
#define POLYMIAL_H
#include "../list-adt/List.h"
#include <iostream>

template<typename T1 = float, typename T2 = int>
struct Item
{
	T1 coef;
	T2 expn;
	Item(T1 c = 0, T2 e = 0):coef(c), expn(e){}
};

template<typename T1, typename T2>
std::ostream & operator<<(std::ostream & os, const Item<T1, T2> & it)
{
	os << "<" << it.coef << "," << it.expn << ">";
	return os;
}

template<typename Item> 
class Polymial: private List<Item>
{
	private:
		typedef List<Item> base;
	public:
		typedef typename base::input_iterator input_iterator;
		typedef typename base::fwd_iterator fwd_iterator;
		Polymial(const Item *is, int ct);
		Polymial(const Polymial & P);
		~Polymial(){}
		Polymial & operator=(const Polymial & P);
		Polymial operator+(const Polymial & p) const;
		Polymial operator-(const Polymial & p) const;
		Polymial operator*(const Polymial & p) const;
		bool puts(const Item *is, int ct);
		bool put(const Item &i);
		bool get_n(int pos, Item & i) const;
		void show()const{base::show();}
		/** */
		input_iterator begin(void) const {return base::begin();}
		input_iterator end(void) const {return base::end();}
		fwd_iterator begin(void)  {return base::begin();}
		fwd_iterator end(void)  {return base::end();}
};


template<typename Item>
Polymial<Item>::
Polymial(const Item *is, int ct):base::List(2 * ct)
{
	int j;
	for(j = 0; j < ct; j++)
	  put(is[j]);
}

/** put item into list according expn*/
template<typename Item>
bool Polymial<Item>::
put(const Item & i)
{
	int pos;
	typename base::input_iterator it;
	for(it = base::begin(); it != base::end(); ++it)
	{
		if(i.expn > (*it).expn) pos++;
		else if(i.expn == (*it).expn) return false;
	}
	return base::insert_n(pos, i);
}

#endif
